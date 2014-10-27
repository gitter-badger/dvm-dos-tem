#include <string>

#include <netcdfcpp.h>

#include "GridData.h"

GridData::GridData() {
};

GridData::~GridData() {
};

void GridData::clear() {
  lat = MISSING_F;
  lon = MISSING_F;
  fill_n(alldaylengths, 365, MISSING_F);
  drgtype = MISSING_I;
  topsoil = MISSING_I;
  botsoil = MISSING_I;
  fri = MISSING_I;
  fill_n(pfsize, NUM_FSIZE, MISSING_D);
  fill_n(pfseason, NUM_FSEASON, MISSING_D);
}

/* Given a file name and "grid record id", sets members lat, lon from file.
 *
 * Note: recid - the order (from ZERO) in the .nc file,
 *       v.s.
 *       gridid - the grid id user-defined in the dataset
 */
void GridData::read_location_from_file(std::string filename, int recid) {

  NcFile grid_file = temutil::open_ncfile(filename);

  NcVar* latV = temutil::get_ncvar(grid_file, "LAT");
  latV->set_cur(recid);
  latV->get(&this->lat, 1);

  NcVar* lonV = temutil::get_ncvar(grid_file, "LON");
  lonV->set_cur(recid);
  lonV->get(&this->lon, 1);

}

/** Given a file name, and "drainage record number", sets drainage member 
* from file.
*/
void GridData::drainage_type_from_file(std::string filename, int rec) {

  NcFile drainage_file = temutil::open_ncfile(filename);

  NcVar* v = temutil::get_ncvar(drainage_file, "DRAINAGETYPE");
  v->set_cur(rec);
  v->get(&this->drgtype, 1);

}

