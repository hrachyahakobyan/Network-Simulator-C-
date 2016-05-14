#pragma once
#include <string>
#include <map>
#include <assert.h>

// Notification strings

static const std::string TIME_TICK_NOTIFICATION = "time_tick_notification";

// Timer

static const int DEFAULT_DURATION_SECONDS = 1;
static const int MAX_DURATION_SECONDS = 100;

static const int MAX_DURATION_MILLISECONDS = MAX_DURATION_SECONDS * 1000;
static const int MIN_DURATION_MILLISECONDS = 10;

// Image extensions

static const std::string IMG_EXT_PDF = "pdf";
static const std::string IMG_EXT_PNG = "png";
static const std::string IMG_EXT_JPG = "jpg";


// Graph types

static const std::string GRAPH_RANDOM = "Random graph";
static const std::string GRAPH_HYPER = "Hypercube graph";
static const std::string GRAPH_KNODEL = "Knodel graph";
static const std::string GRAPH_KTREE = "K-ary tree";
static const std::string GRAPH_BINOMIAL = "Binomial tree";
static const std::string GRAPH_COMPLETE = "Complete graph";
static const std::string GRAPH_GRID = "Grid";
static const std::string GRAPH_TORUS = "Torus";
static const std::string GRAPH_CCC = "CCC";
static const std::string GRAPH_BIPARTITE = "Bipartite";
static const std::string GRAPH_DIPPER = "Dipper";
static const std::string GRAPH_RAND_TREE = "Random Tree";
static const std::string GRAPH_FIXED_RAND_TREE = "Fixed Random Tree";

static const int GRAPH_BINOMIAL_MAX_HEIGHT = 10;
static const int GRAPH_HYPER_MAX_DIM = 5;
static const int GRAPH_KNODEL_MAX_VERTICES = 50;
static const int GRAPH_COMPLETE_MAX_VERTICES = 20;
static const int GRAPH_KTREE_MAX_VERTICES = 150;

// Enums

enum Two_State {uninformed, informed};
enum Color{White, Black, Red, Blue, Green};

// Default color map

static const std::map<int, std::string> DEFAULT_COLOR_MAP = { { 0, "white" }, { 1, "black" }, { 2, "green" }, { 3, "blue" }, { 4, "red" } };
static const std::vector<std::string> RENDER_ENGINES = { "sfdp", "dot", "neato", "fdp", "twopi", "circo", "osage" };
// Render engines

// BroadcastScheme

static const int MAX_TICKS = 100;

static const std::string SEND_SCHEME_M1 = "SendSchemeM1";
static const std::string SEND_SCHEME_M2 = "SendSchemeM2";
static const std::string SEND_SCHEME_M3 = "SendSchemeM3";
static const std::string SEND_SCHEME_RADIO = "SendSchemeRadio";
static const std::string RECEIVE_SCHEME_RADIO = "ReceiveScehemRadio";
static const std::string RECEIVE_SCHEME_M = "ReceiveSchemeM";
static const std::string FINISH_SCHEME_M = "FinishSchemeM";