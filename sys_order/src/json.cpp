#include<iostream>
using namespace std;
#include<jsoncpp/json/json.h>

int main()
{
  int arr[] = {1,2,3};
  Json::Value val;
  val["name"] = "cj";
  for(int i = 0; i < 3; i++)
  {
    val["score"].append(arr[i]);
  }

  Json::FastWriter writer;
  string str = writer.write(val["score"]);
cout << '[' << str <<  ']' << endl;

  return 0;
}

/*
int main()
{
  int score[] = {71, 76, 80, 82};
  Json::Value val;
  val["姓名"] = "陈婕";
  val["性别"] = "女";
  val["年龄"] = 20;
  for(int i = 0; i < 4; i++)
  {
    val["成绩"].append(score[i]);
  }

  //序列化
  Json::StyledWriter writer;
  string ret = writer.write(val);
  cout << ret << endl;
  Json::FastWriter fwriter;
  ret = fwriter.write(val);
  cout << ret << endl;
  //反序列化
  Json::Reader reader;
  Json::Value vals;
  reader.parse(ret, vals);
  cout << vals["姓名"].asString() << endl;
  cout << vals["性别"].asString() << endl;
  cout << vals["年龄"].asInt() << endl;
  int num = vals["成绩"].size();
  for(int i = 0; i < num; i++)
  {
    cout << vals["成绩"][i].asInt() << endl;
  }

}
*/
