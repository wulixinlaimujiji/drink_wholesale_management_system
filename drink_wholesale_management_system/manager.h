#ifndef DRINK_WHOLESALE_MANAGEMENT_SYSTEM_MANAGER_H
#define DRINK_WHOLESALE_MANAGEMENT_SYSTEM_MANAGER_H

#include "public.h"

/*登录部分(管理员端)*/
//登录管理员账号
bool ManagerLogin();
//忘记管理员密码
void ForgotManagerPassword();

/*管理员信息部分(管理员端)*/
//查看管理员信息
void ManagerInformation();
//修改联系方式
void ModifyManagerTel();
//修改管理员密码
void ModifyManagerPassword();

/*用户信息部分(管理员端)*/
//查看用户信息(identity=1为用户，0为管理员)
void UserInformation(User* user, int identity);
//重置用户密码
void ResetUserPassword(User* user);

/*酒水部分(管理员端)*/
//用户查看在售酒水(identity=1为用户，0为管理员)(type=1为单个酒水，0为链表)
void ViewAvailableDrinks(Drink* head, int identity, int type);
//输入酒水查询条件
int InputDrinkConditions(char* brand, char* taste, char* package, char* capacity, char* activity);
//创建按条件搜索酒水链表
Drink* CreatFoundDrinkList(char* brand, char* taste, char* package, char* capacity, char* activity);
//销毁查询酒水链表
void DestroyFoundDrinkList(Drink* head);
//修改销售价格
void ModifyDrinkSalePrice(Drink* drink);
//设置优惠活动
void SetActivity(Drink* head, int type);
//下架酒水
void TakeDownDrink(Drink* head, int type);

/*信息部分(管理员端)*/
//接受下单
void AcceptOrder();
//接受退单
void AcceptReturn();

/*批发部分(管理员端)*/
//查看批发记录(identity=1为用户，0为管理员)(situation=6为所有状态)(type=1为单个记录，0为链表)
void ViewWholesaleRecords(WholesaleRecord* head, User* user, int situation, int type);
//输入查询条件
int ManagerInputWholesaleRecordConditions(char* user, char* date, char* situation, char* brand, char* taste, char* package, char* capacity);
//建立查询批发记录链表
WholesaleRecord* CreatManagerFoundWholesaleRecordList(char* user, char* date, char* situation, char* brand, char* taste, char* package, char* capacity);
//创建临时批发记录链表结点
WholesaleRecord* CreatTempWholesaleRecordListNode(WholesaleRecord* wholesale_record);
//销毁临时批发记录链表
void DestroyTempWholesaleRecordList(WholesaleRecord* head);
//修改订单
void ManagerModifyAnWholesaleOrder(WholesaleRecord* head);

/*进货部分(管理员端)*/
//管理员查看所有的进货记录
void ViewPurchaseRecords(PurchaseRecord* head, int type);
//输入查询条件
int ManagerInputPurchaseRecordConditions(char* date, char* brand, char* taste, char* package, char* capacity);
//建立查询进货记录链表
PurchaseRecord* CreatManagerFoundPurchaseRecordList(char* date, char* brand, char* taste, char* package, char* capacity);
//销毁临时进货记录链表
void DestroyTempPurchaseRecordList(PurchaseRecord* head);
//添加订单
void AddAnPurchaseRecordOrder();
//添加酒水
void AddDrink(PurchaseRecord* purchase_record);
///修改订单
//修改进货记录日期
void ModifyPurchaseRecordDate(PurchaseRecord* purchase_record);
//修改进货酒水品牌
void ModifyPurchaseRecordBrand(PurchaseRecord* purchase_record);
//修改进货酒水口味
void ModifyPurchaseRecordTaste(PurchaseRecord* purchase_record);
//修改进货酒水包装
void ModifyPurchaseRecordPackage(PurchaseRecord* purchase_record);
//修改进货酒水单瓶容量
void ModifyPurchaseRecordBottleCapacity(PurchaseRecord* purchase_record);
//修改进货酒水单箱数量
void ModifyPurchaseRecordBoxQuantity(PurchaseRecord* purchase_record);
//修改酒水进货价格
void ModifyPurchaseRecordRestockingPrice(PurchaseRecord* purchase_record);
//修改酒水进货数量
void ModifyPurchaseRecordGoodsQuantity(PurchaseRecord* purchase_record);

#endif //DRINK_WHOLESALE_MANAGEMENT_SYSTEM_MANAGER_H
