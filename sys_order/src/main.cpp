#include<iostream>
using namespace std;
#include"mysql.hpp"



int main()
{
  order_sys::order_dish order;
  /*
  order.Delete(3);
  order.Delete(4);
  */
  
  Json::Value ord;
  order.SelectOne(2, ord);
  Json::StyledWriter writer;
  string ret = writer.write(ord);
  cout << ret << endl; 
  /*
  Json::FastWriter writer;
  string ret = writer.write(ord);
  cout << ret << endl;
  */
  /*
  order.SelectAll(ord);
  Json::FastWriter writer;
  string ret = writer.write(ord);
  cout << ret << endl;
  */
  /*
  ord["id"] = 5;
  int arr[] = {1,8};
  for(int i = 0; i < 2; i++)
  {
    ord["or_dish"].append(arr[i]);
  }
  ord["status"] = 1;
  order.Update(ord);
  */ 
 
  /*
  order_sys::tb_dish dishes;
  Json::Value dish;
  
  dish["name"] = "宫爆鸡丁";
  dish["price"] = 2700;
  bool ret = dishes.Insert(dish);
  */
  
  /*
  dish["id"] = 3;
  dish["name"] = "水煮肉片";
  dish["price"] = 2500;
  dishes.Update(dish);
  return 0;
  */

  /*
  Json::Value val;
  dishes.SelectOne(1, val);
  /*
  Json::StyledWriter writer;
  string ret = writer.write(val);
  */
/*
  Json::FastWriter writer;
  string ret = writer.write(val);
  cout << ret << endl;
  */ 
}
