#ifndef SIGNALSLIB_HPP_INCLUDED
#define SIGNALSLIB_HPP_INCLUDED 

#if defined(signals) && defined(QOBJECTDEFS_H) && \
  !defined(QT_MOC_CPP)
#  undef signals
#  define signals signals
#endif

#include <boost/signal.hpp>
namespace boost
{
	namespace signalslib = signals;
}

#if defined(signals) && defined(QOBJECTDEFS_H) && \
  !defined(QT_MOC_CPP)
#  undef signals
// Restore the macro definition of "signals", as it was
// defined by Qt's <qobjectdefs.h>.
#  define signals protected
#endif

#include <boost/config.hpp> 
#include <boost/version.hpp> 
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp> 
#include <boost/property_map/property_map.hpp> 
#include <boost/graph/copy.hpp>
#include <boost/static_assert.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#endif