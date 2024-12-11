#define CATCH_CONFIG_MAIN

#include "structures.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Nodes", "[node]") {
  Node<int> node1(0);
  Node<int> node2(1);
  Node<char> node3('b');
  Node<char> node4('c');
  Node<char> node5('a');

  REQUIRE(node1.connect_node(node2, 2));
  REQUIRE(node1.has_edge_to(node2));
  REQUIRE(!node2.has_edges());
  REQUIRE(node1.get_weight(node2) == 2);
  REQUIRE(node1.change_weight(node2, 69));
  REQUIRE(node1.get_weight(node2) == 69);
  
  node1.remove_edge(node2);
  REQUIRE(!node1.has_edge_to(node2));

  REQUIRE(node3.connect_node(node4, 2));
  REQUIRE(node3.connect_node(node5, 50));
  REQUIRE(!node3.connect_node(node5, 0));
}

TEST_CASE("Graph", "[graph]") {
  Graph<int> g;
  REQUIRE(g.add_node(0));
  REQUIRE(g.add_node(1));
  REQUIRE(!g.add_node(1));
  REQUIRE(g.add_node(Node<int>(2)));
  REQUIRE(g.add_node(Node<int>(3)));
  REQUIRE(g.add_node(4));


}