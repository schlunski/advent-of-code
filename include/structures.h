#pragma once

#include <exception>
#include <map>
#include <set>
#include <vector>

template <typename T> class Node {
public:
  // comparer needed for the map
  struct NodeCompare {
    bool operator()(const Node<T> &lhs, const Node<T> &rhs) const {
      return lhs.id < rhs.id;
    }
  };

private:
  // edges from Node to another nodes
  std::map<Node, unsigned, NodeCompare> _edges;

public:
  const T id;
  Node(T id) : id(id) {};

  /**
   * Checks if Node is connected to other Node
   *
   * @param other Node to check the connection to
   */
  const bool has_edge_to(const Node<T> &other) {
    return _edges.find(other) != _edges.end();
  };
  /**
   * Checks if Node has edges to other nodes
   */
  const bool has_edges() { return !_edges.empty(); };
  /**
   * Gets the weight between self and another node
   *
   * @param other node
   *
   * @return weight between self and other, -1 if no connection
   */
  const int get_weight(const Node<T> &other) {
    if (_edges.find(other) == _edges.end())
      return -1;
    return _edges[other];
  };
  /**
   * Connect another node to self
   *
   * @param other node to make connection to
   * @param weight weight to other node
   */
  bool connect_node(const Node<T> &other, const unsigned weight) {
    if (_edges.find(other) != _edges.end() || other.id == id)
      return false;
    _edges.insert({other, weight});
    return true;
  };
  /**
   * Remove edge from node expecting node to be in edges
   *
   * @param node node to remove
   */
  std::pair<Node<T>, unsigned> remove_edge(const Node<T> &node) {
    unsigned weight = _edges[node];
    _edges.erase(_edges.find(node));
    return {node, weight};
  };
  /**
   * Remove edge from by node id
   *
   * @param id id of node to remove expecting node to be in edges
   */
  std::pair<Node<T>, unsigned> remove_edge(const T id) {
    unsigned weight = _edges[Node<T>(id)];
    _edges.erase(_edges.find(Node<T>(id)));
    return {Node<T>(id), weight};
  };
  /**
   * Change the weight to another node
   *
   * @param other node to change the weight with
   * @param newWeight new weight from self to other node
   */
  bool change_weight(const Node<T> &other, const int newWeight) {
    if (_edges.find(other) == _edges.end())
      return false;
    _edges[other] = newWeight;
    return true;
  }
};
/**
 * Datastructure to represent a graph can be directed/undirected and
 * weighted/unweighted
 */
template <typename T> class Graph {
private:
  // comparer needed for the map
  struct NodeCompare {
    bool operator()(const Node<T> &lhs, const Node<T> &rhs) const {
      return lhs.id < rhs.id;
    }
  };

  // Nodes in the graph
  std::set<Node<T>, NodeCompare> _nodes;

public:
  bool weighted = true;
  bool directed = true;
  /**
   * Checks if the graph is empty
   */
  const bool is_empty() { return _nodes.empty(); };
  /**
   * Create a node by given id and add to the graph without edges
   *
   * @param id id to create Node that gets added
   *
   * @return adding node was succesful
   */
  bool add_node(const T id) { return _nodes.insert(Node<T>(id)).second; };
  /**
   * Create a node by given id and add to the graph without edges
   *
   * @param node Node to add
   *
   * @return adding node was succesful
   */
  bool add_node(const Node<T> &node) { return _nodes.insert(node).second; };
  /**
   * Add a node to the graph with edges to all other nodes
   *
   * @param node node to add
   * @param weight weight on edge between nodes
   * @param bidirectional determines if edges are added in both directions
   *
   * @return adding node was succesful
   */
  bool add_node_with_edges(T node, unsigned weight, bool bidirectional);
  /**
   * Add a node to the graph with edges given nodes
   *
   * @param node node to add
   * @param edges mop of destination node with weight
   *
   * @return adding node was succesful
   */
  bool add_node_with_edges(T node);
  /**
   * Remove a Node from graph
   *
   * @return nullptr if Node not in graph
   */
  Node<T> remove_node(const Node<T> node) {
    if (_nodes.find(node) == _nodes.end())
      return nullptr;
    return node;
  };
};