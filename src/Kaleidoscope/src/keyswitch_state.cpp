/* -*- mode: c++ -*-
 * Leidokos-Python -- Wraps Kaleidoscope modules' c++
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

#include "Leidokos-Python.h"

#include "keyswitch_state.h"

namespace leidokos {
namespace python {
   
#define FOR_ALL_FLAGS(FUNC) \
   FUNC(INJECTED) \
   FUNC(IS_PRESSED) \
   FUNC(WAS_PRESSED)
   
#define DEFINE_FLAGS(FLAG) \
   static uint8_t flag_##FLAG() { return FLAG; }
   
FOR_ALL_FLAGS(DEFINE_FLAGS)
   
static bool __keyIsPressed(uint8_t keyState) {
   return keyIsPressed(keyState);
}

static uint8_t __setKeyIsPressed(uint8_t keyState) {
   return keyState | IS_PRESSED;
}

static bool __keyWasPressed(uint8_t keyState) {
   return keyWasPressed(keyState);
}

static uint8_t __setKeyWasPressed(uint8_t keyState) {
   return keyState | WAS_PRESSED;
}

static bool __keyToggledOn(uint8_t keyState) {
   return keyToggledOn(keyState);
}

static bool __keyToggledOff(uint8_t keyState) {
   return keyToggledOff(keyState);
}

static uint8_t __setKeyIsInjected(uint8_t keyState) {
   return keyState | INJECTED;
}

static void exportPython() {
   
   #define REGISTER_FLAGS(FLAG) \
      boost::python::def(#FLAG, &leidokos::python::flag_##FLAG, \
         "Returns flag \"" #FLAG "\".\n\n" \
         "Returns:\n" \
         "   uint8_t: The flag \"" #FLAG "\".");
      
   FOR_ALL_FLAGS(REGISTER_FLAGS)

   boost::python::def("keyIsPressed", &leidokos::python::__keyIsPressed,
      "Tests whether a key is pressed.\n"
      "This is true if the key is pressed during this scan cycle.\n"
      "This will be true for several consecutive cycles even for a single tap of\n"
      "the key.\n"
      "Use this for events which should fire every scan cycle the key is held.\n"
      "If you want an event which fires only once when a key is pressed, use\n"
      "keyToggledOn() or keyToggledOff().\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to test.\n\n"
      "Returns:\n"
      "   bool: Whether the key is pressed.\n"
   );
   
   boost::python::def("setKeyIsPressed", &leidokos::python::__setKeyIsPressed,
      "Sets is-pressed flag for a key.\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to modifiy.\n\n"
      "Returns:\n"
      "   uint8_t: The key with is-pressed flag set.\n"
   );

   boost::python::def("keyWasPressed", &leidokos::python::__keyWasPressed,
      "Tests whether a key was pressed.\n"
      "This is true if the key was pressed during the previous\n"
      "scan cycle, regardless of whether it is pressed or not in this scan cycle.\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to test.\n\n"
      "Returns:\n"
      "   bool: Whether the key was pressed.\n"
   );
   
   boost::python::def("setKeyWasPressed", &leidokos::python::__setKeyWasPressed,
      "Sets was-pressed flag for a key.\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to modifiy.\n\n"
      "Returns:\n"
      "   uint8_t: The key with was-pressed flag set.\n"
   );

   boost::python::def("keyToggledOn", &leidokos::python::__keyToggledOn,
      "Tests whether a is toggled on.\n"
      "This is true if the key is newly pressed during this scan\n"
      "cycle, i.e. was not pressed in the previous scan cycle but is now.\n"
      "Use this for events which should fire exactly once per keypress, on a\n"
      "\"key-down\" event.\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to test.\n\n"
      "Returns:\n"
      "   bool: Whether the key is toggled on.\n"
   );

   boost::python::def("keyToggledOff", &leidokos::python::__keyToggledOff,
      "Tests whether a key is toggled off.\n"
      "This is true if the key is newly not-pressed during this\n"
      "scan cycle, i.e. is not pressed now but was in the previous scan cycle.\n"
      "Use this for events which should fire exactly once per keypress, on a\n"
      "\"key-up\" event.\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to test.\n\n"
      "Returns:\n"
      "   bool: Whether the key is toggled off.\n"
   );
   
   boost::python::def("setKeyIsInjected", &leidokos::python::__setKeyIsInjected,
      "Sets is-injected flag for a key.\n\n"
      "Args:\n"
      "   keyState (uint8_t): The key state to modifiy.\n\n"
      "Returns:\n"
      "   uint8_t: The key with is-injected flag set.\n"
   );
}
      
LEIDOKOS_PYTHON_EXPORT(&exportPython, nullptr)

} // namespace python
} // namespace leidokos
