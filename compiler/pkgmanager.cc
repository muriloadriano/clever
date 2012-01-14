/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include "pkgmanager.h"
#include "cstring.h"
#include "modules/std/std_pkg.h"

namespace clever {

/**
 * Loads native packages
 */
void PackageManager::init() throw() {
	addPackage(CSTRING("std"), new packages::Std());
}

/**
 * Load an entire package
 */
void PackageManager::loadPackage(Scope* scope, const CString* const package) throw() {
	PackageMap::const_iterator it = m_packages.find(package);

	if (it != m_packages.end()) {
		/**
		 * Check if the package already has been loaded
		 */
		if (it->second->isLoaded()) {
			return;
		}
		/**
		 * Initializes the package
		 */
		it->second->init();
		{
			ModuleMap& modules = it->second->getModules();
			ModuleMap::const_iterator it = modules.begin(), end = modules.end();

			while (it != end) {
				loadModule(scope, package, it->second, NULL);
				++it;
			}
		}
		/**
		 * Sets the package state to fully loaded
		 */
		it->second->setFullyLoaded();
	} else {
		std::cerr << "package '" << *package << "' not found" << std::endl;
	}
}

/**
 * Loads an specific module
 */
void PackageManager::loadModule(Scope* scope, const CString* const package,
	Module* const module, const CString* const alias) throw() {
	/**
	 * Checks if the module already has been loaded
	 */
	if (module->isLoaded()) {
		return;
	}
	/**
	 * Initializes the module
	 */
	module->init();
	{
		const std::string prefix_name = alias ?
			alias->str() + "::" : package->str() + "." + module->getName() + "::";

		FunctionMap& funcs = module->getFunctions();
		FunctionMap::const_iterator it = funcs.begin(), end = funcs.end();

		/**
		 * Inserts the function into the symbol table
		 */
		while (it != end) {
			CallableValue* fvalue = new CallableValue(CSTRING(it->first));

			fvalue->setHandler(it->second);

			scope->bind(CSTRING(prefix_name + *fvalue->getName()), fvalue);
			scope->bind(fvalue->getName(), fvalue);
			fvalue->addRef();
			++it;
		}

		ClassMap& classes = module->getClassTable();
		ClassMap::iterator itc = classes.begin(), endc = classes.end();

		/**
		 * Inserts all classes into the symbol table
		 */
		while (itc != endc) {
			g_symtable.push(CSTRING(prefix_name + *itc->first), itc->second);
			g_symtable.push(itc->first, itc->second);
			itc->second->addRef();
			++itc;
		}

		ConstMap& constants = module->getConstants();
		ConstMap::iterator itcs = constants.begin(), endcs = constants.end();

		/**
		 * Inserts all constants into the symbol table
		 */
		while (itcs != endcs) {
			g_symtable.push(CSTRING(prefix_name + itcs->first->str()), itcs->second);
			++itcs;
		}
	}
	/**
	 * Sets the module state to loaded
	 */
	module->setLoaded();
}

/**
 * Loads an specific module package by supplying the package and module names
 */
void PackageManager::loadModule(Scope* scope, const CString* const package,
	const CString* const module, const CString* const alias) throw() {
	PackageMap::const_iterator it = m_packages.find(package);

	if (it != m_packages.end()) {
		/**
		 * Checks if the package is unloaded, in this case initialize it
		 */
		if (it->second->isUnloaded()) {
			it->second->init();
		}
		/**
		 * Check if the package already has been fully loaded
		 */
		if (!it->second->isFullyLoaded()) {
			ModuleMap& modules = it->second->getModules();
			ModuleMap::const_iterator it_mod = modules.find(module);

			/**
			 * Loads the module if it has been found
			 */
			if (it_mod != modules.end()) {
				loadModule(scope, package, it_mod->second, alias);
			}
		}
		/**
		 * Change the package state to loaded
		 */
		it->second->setLoaded();
	}
}

/**
 * Removes the packages and its modules
 */
void PackageManager::shutdown() throw() {
	PackageMap::const_iterator it = m_packages.begin(), end = m_packages.end();

	while (it != end) {
		ModuleMap& modules = it->second->getModules();
		ModuleMap::const_iterator it_module = modules.begin(), end_module = modules.end();

		/**
		 * Deletes the module entries
		 */
		while (it_module != end_module) {
			delete it_module->second;
			++it_module;
		}
		/**
		 * Deletes the package
		 */
		delete it->second;
		++it;
	}
}

} // clever
