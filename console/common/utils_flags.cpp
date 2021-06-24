/*
The GeoViz console applications implement algorithmic geo-visualization
methods, developed at TU Eindhoven.
Copyright (C) 2021  Netherlands eScience Center and TU Eindhoven

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Created by tvl (t.vanlankveld@esciencecenter.nl) on 10-02-2020
*/

#include "utils_flags.h"

#include "console/common/utils_filesystem.h"


namespace validate
{

bool IsFile(const std::string& value)
{
  return !IsDirectory(value);
}

bool IsDirectory(const std::string& value)
{
  try
  {
    return filesystem::is_directory(value);
  }
  catch (const std::exception& e)
  {
    LOG(INFO) << e.what();
    return false;
  }
}

bool ExistsFile(const std::string& value)
{
  try
  {
    return filesystem::is_regular_file(value) && ExistsPath(value);
  }
  catch (const std::exception& e)
  {
    LOG(INFO) << e.what();
    return false;
  }
}

bool ExistsDirectory(const std::string& value)
{
  try
  {
    return IsDirectory(value) && ExistsPath(value);
  }
  catch (const std::exception& e)
  {
    LOG(INFO) << e.what();
    return false;
  }
}

bool ExistsPath(const std::string& value)
{
  try
  {
    return filesystem::exists(value);
  }
  catch (const std::exception& e)
  {
    LOG(INFO) << e.what();
    return false;
  }
}

bool AvailableFile(const std::string& value)
{
  try
  {
    filesystem::path path(value);
    if (path.has_parent_path() && !ExistsDirectory(path.parent_path()))
      return false;
    return IsFile(value) && !ExistsPath(value);
  }
  catch (const std::exception& e)
  {
    LOG(INFO) << e.what();
    return false;
  }
}

bool MakeAvailableFile(const std::string& value)
{
  try
  {
    filesystem::path path(value);
    if (path.has_parent_path())
    {
      if (!ExistsDirectory(path.parent_path()))
        filesystem::create_directories(path.parent_path());
      return ExistsDirectory(path.parent_path());
    }
    return true;
  }
  catch (const std::exception& e)
  {
    LOG(INFO) << e.what();
    return false;
  }
}

bool Empty(const std::string& value)
{
  return value.empty();
}

} // namespace validate