// This file has been generated by Py++.

#include "boost/python.hpp"
#include "indexing_suite/container_suite.hpp"
#include "indexing_suite/vector.hpp"
#include "generators/include/python_CEGUI.h"
#include "_PropertyInitialiser__value_traits.pypp.hpp"
#include "PropertyInitialiserVector.pypp.hpp"

namespace bp = boost::python;

void register_PropertyInitialiserVector_class(){

    { //::std::vector< CEGUI::PropertyInitialiser >
        typedef bp::class_< std::vector< CEGUI::PropertyInitialiser > > PropertyInitialiserVector_exposer_t;
        PropertyInitialiserVector_exposer_t PropertyInitialiserVector_exposer = PropertyInitialiserVector_exposer_t( "PropertyInitialiserVector" );
        bp::scope PropertyInitialiserVector_scope( PropertyInitialiserVector_exposer );
        PropertyInitialiserVector_exposer.def( bp::indexing::vector_suite< std::vector< CEGUI::PropertyInitialiser > >() );
    }

}
