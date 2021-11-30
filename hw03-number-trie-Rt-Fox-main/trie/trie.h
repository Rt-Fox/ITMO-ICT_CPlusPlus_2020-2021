#pragma once

#include <string>
#include <vector>

#include <map>

struct node_t {
  size_t count{0};
  size_t subtree_count{0};
  std::map<char, node_t> next;
};
class trie_t {
private:
  node_t root; // верхий элемент, он же корень равен пустоте
  void insert_dop(node_t &node, const std::string &str);
  bool erase_dop(node_t &node, const std::string &str);
  bool find_dop(const node_t &node, const std::string &str) const;
  size_t count_with_prefix_dop(const node_t &node, const std::string &prefix) const;
  void index_dop(std::string &answer, const node_t &node,size_t index) const;
  void to_vector_dop(std::string str, std::vector<std::string> &answer, const node_t &node) const;

public:
  trie_t();
  ~trie_t();

  trie_t(const trie_t &other);
  trie_t &operator=(const trie_t &other);

  /**
   * Insert specified string
   * @param str
   */
  void insert(const std::string &str);
  /**
   * Remove specified string
   * @param str
   * @return return true if specified string was in container
   */
  bool erase(const std::string &str);
  /**
   * Made your container empty
   */
  void clear();

  /**
   * @param str
   * @return true if there is at least one specified string in your container
   */
  bool find(const std::string &str) const;
  /**
   * @param prefix
   * @return number of strings which starts with specified prefix in your container
   */
  size_t count_with_prefix(const std::string &prefix) const;

  /**
   * IMAGINE that you sort all strings in you container in lexicographic order.
   * You should return string on position index in this order
   * @param index
   */
  std::string operator[](size_t index) const;

  /**
   * @return All strings from your container in lexicographic order.
   */
  std::vector<std::string> to_vector() const;

  /**
   * @return Number of strings in container
   */
  size_t size() const;
  /**
   * @return true if container is empty :)
   */
  bool empty() const;

  /**
   * Exchange content of this and other
   * @param other
   */
  void swap(trie_t &other);
};
