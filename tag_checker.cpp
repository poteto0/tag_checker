#include <iostream>
#include <fstream>
#include <map>
using namespace std;

string str;
map<string, int> tag_count;
vector<string> target_plus_tag = {"<tr>","<td","<th"};
vector<string> target_minus_tag = {"</tr>","</td>","</th>"};

template<class T> bool contain(const string& s, const T& v) {
   return s.find(v) != string::npos;
}

int contains_at(vector<string> tag_list){
  int i=0;
  for(auto tag: tag_list) {
    if(contain(str, tag)) return i;
    i++;
  }
  return -1;
}

bool minus_check(){
  bool flag = true;
  for(int i=0; i<target_plus_tag.size(); i++){
    string plus_str = target_plus_tag[i], minus_str = target_minus_tag[i];
    int plus  = (!tag_count[plus_str])  ? 0 : tag_count[plus_str];
    int minus = (!tag_count[minus_str]) ? 0 : tag_count[minus_str];

    flag &= (plus >= minus);
  }
  return flag;
}

int find_not_zero(){
  for(int i=0; i<target_plus_tag.size(); i++){
    string plus_str = target_plus_tag[i], minus_str = target_minus_tag[i];
    int plus  = (!tag_count[plus_str])  ? 0 : tag_count[plus_str];
    int minus = (!tag_count[minus_str]) ? 0 : tag_count[minus_str];

    if(plus != minus) return i;
  }
  return -1;
}

int main(int argc, char const *argv[]){
  ifstream target(argv[1]);
  if(!target.is_open()){ cout << "Failed to open " << argv[1] << endl; return 1; }

  int line = 0;
  while(getline(target,str)) {
    line++;

    // +
    int p = /* str */ contains_at(target_plus_tag);
    if(p >= 0) {
      string c = target_plus_tag[p];

      if(!tag_count[c]) tag_count[c] = 1;
      else tag_count[c]++;
    }

    // -
    int m = /* str */ contains_at(target_minus_tag);
    if(m >= 0) {
      string c = target_minus_tag[m];

      if(!tag_count[c]) tag_count[c] = 1;
      else tag_count[c]++;
    }

    if(!minus_check()) {
      cout << "Over " << str << " at " << line << " lines. " << endl;
      return 0;
    }

  }

  int z = find_not_zero();
  if(z != -1){
    cout << "No" << endl;
    string plus_str = target_plus_tag[z], minus_str = target_minus_tag[z];
    cout << "plus: "  << plus_str  << ", count: " << tag_count[plus_str]  << endl;
    cout << "minus: " << minus_str << ", count: " << tag_count[minus_str] << endl;
    return 0;
  }

  cout << "OK" << endl;
  
  return 0;
}