#include "trie.h"


trie_t::trie_t() = default;
trie_t::~trie_t() = default;
trie_t::trie_t(const trie_t &other)  = default;
trie_t &trie_t::operator=(const trie_t &other) = default;

void trie_t::insert(const std::string &str) {
  if (str == "") {
    root.count++;
    root.subtree_count++;
    return;
  }
  insert_dop(root, str);
}
void trie_t::insert_dop(node_t &node,const std::string &str) {
  auto it = node.next.find(str[0]);
  node.subtree_count += 1;
  if (it == node.next.end()) {
    it = node.next.emplace(str[0], node_t {}).first;
  }
  if (str.length() == 1) {
    (*it).second.count++;
    (*it).second.subtree_count++;
    return;
  }
  insert_dop( (*it).second, str.substr(1));
}
bool trie_t::erase(const std::string &str) {
  if (str == "") {
    if(root.count > 0) {
      root.count--;
      root.subtree_count--;
      return true;
    } else {
      return false;
    }
  }
  return erase_dop(root, str);;
}
bool trie_t::erase_dop(node_t &node, const std::string &str) {
  auto it = node.next.find(str[0]);
  if (it == node.next.end()) {
    //такой строки не существует
    return false;
  }
  if (str.length() == 1) {
    if ((*it).second.count == 0 ) {
      //такой строки нет в дереве
      return false;
    }
    if ((*it).second.subtree_count > 1) {
      (*it).second.count--;
      (*it).second.subtree_count--;
    } else {
      node.next.erase(it);
    }
    node.subtree_count--;
    return true;
  }
  if(erase_dop( (*it).second, str.substr(1))) {
    node.subtree_count--;
    if(node.subtree_count == 0) {
      node.next.erase(it);
    }
    return true;
  } else {
    return false;
  }
}

void trie_t::clear() {
  *this = trie_t();
}

bool trie_t::find(const std::string &str) const {
  if (str == "") {
    return true;
  }
  return find_dop(root, str);
}
bool trie_t::find_dop(const node_t &node, const std::string &str) const {
  auto it = node.next.find(str[0]);
  if (it == node.next.end()) {
    return false;
  }
  if (str.length() == 1) {
    return (*it).second.count > 0;
  }
  return find_dop((*it).second, str.substr(1));
}
size_t trie_t::count_with_prefix(const std::string &prefix) const {
  if (prefix == "") {
    return root.subtree_count;
  }
  return count_with_prefix_dop(root, prefix);
}
size_t trie_t::count_with_prefix_dop(const node_t &node, const std::string &prefix) const {
  auto it = node.next.find(prefix[0]);
  if (it == node.next.end()) {
    return 0;
  }
  if (prefix.length() == 1) {
    return (*it).second.subtree_count;
  }
  return count_with_prefix_dop((*it).second, prefix.substr(1));
}
size_t trie_t::size() const {
  return root.subtree_count;
}
bool trie_t::empty() const {
  return root.subtree_count == 0;
}
void trie_t::swap(trie_t &other) {
  std::swap(*this, other);
}
std::string trie_t::operator[](size_t index) const {
  std::string answer;
  if (root.count > index) {
    return answer;
  }
  index_dop(answer, root, index-root.count);
  return answer;
}
void trie_t::index_dop(std::string &answer, const node_t &node, size_t index) const{
  for (const auto &pair : node.next) {
    if (pair.second.count <= index) {
      if (pair.second.subtree_count >= index+1) {
        answer += pair.first;
        index_dop(answer, pair.second, index - pair.second.count);
        return;
      } else {
        index -= pair.second.subtree_count;
      }
    } else {
      answer += pair.first;
      return;
    }
  }
}
std::vector<std::string> trie_t::to_vector() const {
  std::vector<std::string> answer;
  std::string str;
  to_vector_dop(str,answer, root);
  return answer;
}
void trie_t::to_vector_dop(std::string str, std::vector<std::string> &answer, const node_t &node) const {
  for (int i =0; i < node.count; i++) {
    answer.push_back(str);
  }
  for (const auto &pair : node.next) {
    to_vector_dop(str+ pair.first,answer, pair.second);
  }
}
