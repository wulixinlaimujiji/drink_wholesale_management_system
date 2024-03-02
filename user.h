#ifndef DRINK_WHOLESALE_MANAGEMENT_SYSTEM_USER_H
#define DRINK_WHOLESALE_MANAGEMENT_SYSTEM_USER_H
#include "public.h"

/*登录部分(用户端)*/
//登录账号
User* UserLogin();
//注册账号
void UserSignUp();
//忘记密码
void ForgotUserPassword();

/*个人信息部分(用户端)*/
//修改网点名称
void ModifyUserName(User* user);
//修改网点地址
void ModifyUserAddress(User* user);
//修改联系方式
void ModifyUserTel(User* user);
//修改用户密码
void ModifyUserPassword(User* user);
//充值余额
void UserRecharge(User* user);

/*酒水部分(用户端)*/
//选择酒水加入购物车
void AddDrinkToTheCart(User* user, Drink* head);
//选择酒水直接下单
void PayForDrink(User* user, Drink* head);
//添加批发记录(未下单)
WholesaleRecord* AddWholesaleRecord(User* user, Drink* drink, int boxes);
//计算折扣后价格
float CalculateDiscountedPrice(User* user, Drink* drink, char* current_time, int boxes);
//计算赠送箱数
int CalculateGiftBoxes(Drink* drink, char* current_time, int boxes);
//更新未下单到下单的批发记录(未下单->已下单)
void RenewWholesaleRecord(User* user, Drink* drink, WholesaleRecord* wholesale_record, char* current_time);

/*购物车部分(用户端)*/
//建立用户购物车链表
WholesaleRecord* CreatUserShoppingCartList(User* user);
//查看用户购物车
void ViewUserShoppingCart(User* user, WholesaleRecord* cart_head, int type);
//修改订单
void UserModifyAnOrder(User* user, WholesaleRecord* cart_head);
//选择订单下单
void PayForAnOrder(User* user, WholesaleRecord* cart_head);
//全选下单
void PayForAllOrder(User* user, WholesaleRecord* cart_head);
//从购物车中删除订单
void DeleteAnOrder(User* user, WholesaleRecord* wholesale_record);
//清空购物车
void ClearShoppingCart(User* user, WholesaleRecord* cart_head);

/*批发记录部分(用户端)*/
//申请退货
void UserApplicationForReturn(User* user, WholesaleRecord* head);
//输入查询条件
int UserInputWholesaleRecordConditions(char* date, char* situation, char* brand, char* taste, char* package, char* capacity);
//创建查询批发记录链表
WholesaleRecord* CreatUserFoundWholesaleRecordList(char* date, char* situation, char* brand, char* taste, char* package, char* capacity);

#endif //DRINK_WHOLESALE_MANAGEMENT_SYSTEM_USER_H
