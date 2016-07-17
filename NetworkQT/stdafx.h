#pragma once

#include "targetver.h"
#include <vld.h> 
#include <boost/asio.hpp>
#include "Constants.h"
#include <boost/config.hpp> 
#include <boost/version.hpp> 
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp> 
#include <boost/property_map/property_map.hpp> 
#include <boost/graph/copy.hpp>
#include <boost/static_assert.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/graph/graphviz.hpp>

#include <QtWidgets>
#include <qtextstream.h>
#include <qdebug.h>

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <set>

#include "HNAGraph.h"
/*Singletons*/
//#include "CleanUp.h"
//#include "FileManager.h"
//#include "RandomManager.h"
//#include "TimeManager.h"
//#include "GraphManager.h"
//#include "DefaultNotificationCenter.h"
//
///*Builders*/
//#include "GraphBuilder.h"
