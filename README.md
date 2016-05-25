# networks-aua-app
A network simulator in C++

* Introduction
* Graph topologies
* Broadcast models
* Use in epidemilogy


INTRODUCTION
------------

Network, also referred to as a graph, is a mathematical model used to representd objects that are connected by links.
For more information, check the wiki link for graphs

https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)

The programs allows the research and statistical analysis of graphs from a research point of view. Unlike network simulators such as
NS3 or NS2, the program aims to allow analysis of graphs in terms of broadcasting, which is the process of information dissemination

http://www.cs.toronto.edu/~tomhart/broadcasting/home.html

The program supports simulation on various graph topologies which will be described later.
The program supports simulation of different broadcast schemes which will be described later.

The program also provides an application of broadcast theory on graphs by extending to network models in epidemiology

http://www4.ncsu.edu/~allloyd/pdf_files/network_preprint.pdf

The program uses extensivel the Boost library for graphs

http://www.boost.org/doc/libs/1_58_0/libs/graph/doc/

Qt framework for UI

https://www.qt.io/

and GraphViz library for graph visualization

http://www.graphviz.org/

The program was created as a part of University course prohect on Theory of Communication Networks in the American University of Armenia


