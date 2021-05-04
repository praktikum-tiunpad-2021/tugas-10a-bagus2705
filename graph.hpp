#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace strukdat {

template <typename VertexType>
class graph {
  /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
  using list_type = std::unordered_set<VertexType>;
  using adj_list_type = std::unordered_map<VertexType, list_type>;

 public:
  /**
   * @brief Default constructor.
   *
   * @constructor
   */
  graph() {}

  /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
  void add_vertex(const VertexType &val) {
    _adj_list.insert(std::make_pair(val, list_type()));
  }

  void remove_vertex(const VertexType &val) {
    _adj_list.erase(val);
  }

  /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
  void add_edge(const VertexType &val1, const VertexType val2) {
    _adj_list[val1].insert(val2);
    _adj_list[val2].insert(val1);
  }

  /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
  void remove_edge(const VertexType &val1, const VertexType &val2) {
    _adj_list[val1].erase(val2);
    _adj_list[val2].erase(val1);
  }

  /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
  size_t order() const {
    return _adj_list.size();
  }

  /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
  bool is_edge(const VertexType &val1, const VertexType &val2) const {
    // TODO: Implementasikan!
    if(_adj_list.at(val1).find(val2) == _adj_list.at(val1).end()){
      return false;
    }else if(_adj_list.at(val2).find(val1) == _adj_list.at(val2).end()){
      return false;
    }else return true;
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void bfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    std::unordered_map<VertexType, bool> visited;
    for(auto node = _adj_list.begin(); node != _adj_list.end(); node++){
      visited.insert(std::make_pair(node->first, false));
    }
    std::vector<VertexType> queue;
    queue.push_back(root);
    visited[root] = true;
    while(!queue.empty()){
      VertexType temp = queue.front();
      queue.erase(queue.begin());
      func(temp);
      for(auto node= _adj_list.at(temp).begin(); node != _adj_list.at(temp).end();node++){
        if(!visited[*node]){
          visited[*node] = true;
          queue.push_back(*node);
        }
      }
    }
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void dfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    std::unordered_map<VertexType, bool> visited;
    for(auto node = _adj_list.begin(); node != _adj_list.end(); node++){
      visited.insert(std::make_pair(node->first, false));
    }
    std::vector<VertexType> stack;
    stack.insert(stack.begin(), root);
    while(!stack.empty()){
      VertexType temp = stack.front();
      if(!visited[temp]){
        visited[temp] = true;
        func(temp);
      }
      auto it = _adj_list.at(temp).begin();
      while(it != _adj_list.at(temp).end()){
        if(!visited[*it]){
          temp = *it;
          stack.insert(stack.begin(), temp);
          break;
        }
        it++;
      }
      if(it == _adj_list.at(temp).end()){
        temp = stack.front();
        stack.erase(stack.begin());
      }
    }
  }
 private:
  /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
  adj_list_type _adj_list;
};

}  // namespace strukdat