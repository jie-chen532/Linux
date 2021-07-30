#include<iostream>
#include"httplib.h"
#include"mysql.hpp"
#include<jsoncpp/json/json.h>

#define SROOT "./wwwRoot" 
using namespace std;
using namespace httplib;

order_sys::tb_dish* t_dish = NULL;
order_sys::order_dish* t_ord = NULL;

void InsertDish(const Request& req, Response& res)
{
  Json::Value val;
  Json::Reader read;
  bool ret = read.parse(req.body, val);
  if(ret == false)
  {
    res.status = 400;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "dish info parse failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  ret = t_dish->Insert(val);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "dish insert failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  return;
}

void UpdateDish(const Request& req, Response& res)
{
  Json::Value val;
  Json::Reader read;
  bool ret = read.parse(req.body, val);
  if(ret == false)
  {
    res.status = 400;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "update dish info parse failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  val["id"] = stoi(req.matches[1]);
  ret = t_dish->Update(val);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "update dish failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  return;
}

void DeleteDish(const Request& req, Response& res)
{
  //matches中会解析正则表达式中的id，存放到matches[1]
  //matches[0]中是整个正则表达式
  int id = stoi(req.matches[1]);
  bool ret = t_dish->Delete(id);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "Failed";
    reason["reason"] = "Delete dish failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  return;
}

void SelectOneDish(const Request& req, Response& res)
{
  int dish_id = stoi(req.matches[1]);
  Json::Value dish;
  bool ret = t_dish->SelectOne(dish_id, dish);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "Failed";
    reason["reason"] = "Select One  dish failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  Json::FastWriter writer;
  res.body = writer.write(dish);
  return;
}

void SelectAll(const Request& req, Response& res)
{
  Json::Value dishes;
  bool ret = t_dish->SelectAll(dishes);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "Failed";
    reason["reason"] = "Select All dish failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  Json::FastWriter writer;
  res.body = writer.write(dishes);
  return;
}

void InsertOrder(const Request& req, Response& res)
{
  Json::Value val;
  Json::Reader read;
  bool ret = read.parse(req.body, val);
  if(ret == false)
  {
    res.status = 400;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "order info parse failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  ret = t_ord->Insert(val);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "order insert failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
}

void DeleteOrder(const Request& req, Response& res)
{
  int id = stoi(req.matches[1]);
  bool ret = t_ord->Delete(id);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "Failed";
    reason["reason"] = "Delete order failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
}

void UpdateOrder(const Request& req, Response& res)
{
  Json::Value val;
  Json::Reader read;
  bool ret = read.parse(req.body, val);
  if(ret == false)
  {
    res.status = 400;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "update order info parse failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  val["id"] = stoi(req.matches[1]);
  ret = t_ord->Update(val);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "False";
    reason["reason"] = "update order failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
}

void SelectAllOrder(const Request& req, Response& res)
{
  Json::Value orders;
  bool ret = t_ord->SelectAll(orders);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "Failed";
    reason["reason"] = "Select All order failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  Json::FastWriter writer;
  res.body = writer.write(orders);
}

void SelectOneOrder(const Request& req, Response& res)
{
  int order_id = stoi(req.matches[1]);
  Json::Value order;
  bool ret = t_ord->SelectOne(order_id, order);
  if(ret == false)
  {
    res.status = 500;
    Json::Value reason;
    Json::FastWriter writer;
    reason["result"] = "Failed";
    reason["reason"] = "Select One order failed";
    res.body = writer.write(reason);
    res.set_header("Content-type", "application/json");
    return;
  }
  res.status = 200;
  Json::FastWriter writer;
  res.body = writer.write(order);
}


int main()
{
  Server server;
  server.set_base_dir(SROOT);
  t_dish = new order_sys::tb_dish();
  t_ord = new order_sys::order_dish();

  //正则表达式：（\d+）表示匹配一个数字字符一次或多次
  //R"()" 表示括号中的字符串去除特殊字符的特殊含义
  //dish
  server.Post("/dish", InsertDish);//增加dish
  server.Delete(R"(/dish/(\d+))", DeleteDish);//删除某一dish
  server.Put(R"(/dish/(\d+))", UpdateDish);//修改dish
  server.Get("/dish", SelectAll);//获得dish全部信息
  server.Get(R"(/dish/(\d+))", SelectOneDish);//获取某一dish
  //order
  server.Post("/order", InsertOrder);//增加order
  server.Delete(R"(/order/(\d+))", DeleteOrder);//删除某一order
  server.Get(R"(/order/(\d+))", SelectOneOrder);//获取某一order
  server.Get("/order", SelectAllOrder);//获取全部order
  server.Put(R"(/order/(\d+))", UpdateOrder);//修改order
  server.listen("0.0.0.0", 9000);
  return 0;
}
