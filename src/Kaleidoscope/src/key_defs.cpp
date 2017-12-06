/* -*- mode: c++ -*-
 * Kaleidoscope-Python -- Wraps Kaleidoscope modules' c++
 *    code to be available in Python programs.
 * Copyright (C) 2017 noseglasses <shinynoseglasses@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Kaleidoscope-Python.h"

#include "key_defs.h"

#define FOR_ALL_HELD_MODIFIERS(FUNC) \
   FUNC(KEY_FLAGS) \
   FUNC(CTRL_HELD) \
   FUNC(LALT_HELD) \
   FUNC(RALT_HELD) \
   FUNC(SHIFT_HELD) \
   FUNC(GUI_HELD) \
   FUNC(SYNTHETIC) \
   FUNC(RESERVED)

#define FOR_ALL_MODIFIERS(FUNC) \
   FUNC(LCTRL) \
   FUNC(LALT) \
   FUNC(RALT) \
   FUNC(LSHIFT) \
   FUNC(LGUI)
   
#define FOR_ALL_KEY_TYPE_FLAGS(FUNC) \
   FUNC(IS_SYSCTL) \
   FUNC(IS_CONSUMER) \
   FUNC(SWITCH_TO_KEYMAP) \
   FUNC(IS_INTERNAL) \
   
#define FOR_ALL_HID_TYPES(FUNC) \
   FUNC(HID_TYPE_LC) \
   FUNC(HID_TYPE_NARY) \
   FUNC(HID_TYPE_OOC) \
   FUNC(HID_TYPE_OSC) \
   FUNC(HID_TYPE_RTC) \
   FUNC(HID_TYPE_SEL)
   
namespace kaleidoscope {
namespace python {
      
#define DEFINE_MODIFIER_FUNCTIONS(MOD) \
   static Key_ m_##MOD(const Key_ &key) { return MOD(key); }
   
FOR_ALL_MODIFIERS(DEFINE_MODIFIER_FUNCTIONS)

#define DEFINE_HELD_MODIFIER_FUNCTIONS(MOD) \
   static uint8_t hm_##MOD() { return MOD; }
   
FOR_ALL_HELD_MODIFIERS(DEFINE_HELD_MODIFIER_FUNCTIONS)

#define DEFINE_KEY_TYPE_FLAGS(FLAG) \
   static uint8_t flag_##FLAG() { return FLAG; }
   
FOR_ALL_KEY_TYPE_FLAGS(DEFINE_KEY_TYPE_FLAGS)

#define DEFINE_HID_TYPE_FLAG(FLAG) \
   static uint8_t flag_##FLAG() { return FLAG; }
   
FOR_ALL_HID_TYPES(DEFINE_HID_TYPE_FLAG)

#define FOR_ALL_SPECIAL_KEYS(FUNC) \
   FUNC(NoKey) \
   FUNC(skip) \
   FUNC(Transparent)
   
#define DEFINE_KEY_FUNCTIONS(KEY) \
   static Key_ k_##KEY() { return Key_##KEY; }

FOR_ALL_SPECIAL_KEYS(DEFINE_KEY_FUNCTIONS)

#define FOR_ALL_LIGHT_KEYS(FUNC) \
   FUNC(BacklightDown) \
   FUNC(BacklightUp) \
   FUNC(RFN2) \
   FUNC(LFN2)
   
FOR_ALL_LIGHT_KEYS(DEFINE_KEY_FUNCTIONS)

static const char *modifierToName(uint8_t modifier) {
   
   switch(modifier) {
      
#define DEFINE_MOD_CASE(MOD) \
      case MOD: \
         return #MOD; \
         break;
      
      FOR_ALL_HELD_MODIFIERS(DEFINE_MOD_CASE)
   }

   return "";
}


static void registerPythonStuff() {
   
   using namespace boost::python;
   
   class_<Key_>("Key",
      "Provides functionality to deal with and to represent keys."
   )
      .def(self == uint16_t())
      .def(self == Key_())
//       .def(self = uint16_t())
      .def(self != Key_())
      .def(self >= uint16_t())
      .def(self <= uint16_t())
      .def(self > uint16_t())
      .def(self < uint16_t())
      .def(self >= Key_())
      .def(self <= Key_())
      .def(self > Key_())
      .def(self < Key_())
     ;
         
   #define REGISTER_MODIFIER_FUNCTIONS(MOD) \
      boost::python::def("add"#MOD, &kaleidoscope::python::m_##MOD, \
         "Adds modifier \"" #MOD "\" to a key.\n\n" \
         "Returns:\n" \
         "   Key: The key with modifier \"" #MOD "\" enabled.");
      
   FOR_ALL_MODIFIERS(REGISTER_MODIFIER_FUNCTIONS)
      
   #define REGISTER_HELD_MODIFIER_FUNCTIONS(MOD) \
      boost::python::def("mod"#MOD, &kaleidoscope::python::hm_##MOD, \
         "Returns the modifier identifier \"" #MOD "\".\n\n" \
         "Returns:\n" \
         "   int: The key modifier identifier \"" #MOD "\"." \
      );
      
   FOR_ALL_HELD_MODIFIERS(REGISTER_HELD_MODIFIER_FUNCTIONS)
      
   #define REGISTER_KEY_TYPE_FLAGS(FLAG) \
      boost::python::def("flag"#FLAG, &kaleidoscope::python::flag_##FLAG, \
         "Returns the flag \"" #FLAG "\".\n\n" \
         "Returns:\n" \
         "   int: The flag identifier \"" #FLAG "\"." \
      );
      
   FOR_ALL_KEY_TYPE_FLAGS(REGISTER_KEY_TYPE_FLAGS)
      
   #define REGISTER_HID_TYPE_FLAG(FLAG) \
      boost::python::def("flag"#FLAG, &kaleidoscope::python::flag_##FLAG, \
         "Returns the flag \"" #FLAG "\".\n\n" \
         "Returns:\n" \
         "   int: The flag identifier \"" #FLAG "\"." \
      );
      
   FOR_ALL_HID_TYPES(REGISTER_HID_TYPE_FLAG)
         
   #define EXPORT_KEY_FUNCTIONS(KEY) \
      boost::python::def("key"#KEY, &kaleidoscope::python::k_##KEY, \
         "Returns the key \"" #KEY "\".\n\n" \
         "Returns:\n" \
         "   Key: The key \"" #KEY "\"." \
      );
      
   FOR_ALL_LIGHT_KEYS(EXPORT_KEY_FUNCTIONS)
      
   FOR_ALL_SPECIAL_KEYS(EXPORT_KEY_FUNCTIONS)
   
   boost::python::def("modifierToName", &modifierToName,
         "Maps a modifier ID to its associated name.\n\n"
         "Args:\n"
         "   modifier (int): The modifier ID to map.\n\n"
         "Returns:\n"
         "   string: The modifier name.");
}
      
KALEIDOSCOPE_PYTHON_REGISTER_MODULE(registerPythonStuff)

} // namespace python
} // namespace kaleidoscope