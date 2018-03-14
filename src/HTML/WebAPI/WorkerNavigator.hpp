/*******************************************************************************
 * WorkerNavigator.hpp
 * Copyright (C) 2018  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of html2LaTeX.
 *
 * html2LaTeX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * html2LaTeX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with html2LaTeX.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
#ifndef SRC_HTML_WEBAPI_WORKERNAVIGATOR_HPP_
#define SRC_HTML_WEBAPI_WORKERNAVIGATOR_HPP_

#include "NavigatorConcurrentHardware.hpp"
#include "NavigatorID.hpp"
#include "NavigatorLanguage.hpp"
#include "NavigatorOnLine.hpp"


namespace HTML {
namespace WebAPI {

class WorkerNavigator : public NavigatorID, public NavigatorLanguage, public NavigatorOnLine, public NavigatorConcurrentHardware {

};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_WORKERNAVIGATOR_HPP_ */
