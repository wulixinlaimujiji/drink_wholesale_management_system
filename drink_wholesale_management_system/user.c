#include "user.h"
#include "manager.h"
extern Manager* manager;
extern User* user_head;
extern Drink* drink_head;
extern WholesaleRecord* wholesaleRecord_head;
extern PurchaseRecord* purchaseRecord_head;

/*登录部分*/
//登录用户账号
User* UserLogin() {
    char input[MaxSize] = { "" };
    while (true) {
        //查找账号
        User* user = NULL;
        while (true) {
            system("cls");
            //输入账号或联系方式
            printf("请输入账号或联系方式(输入0返回)：");
            fgets(input, sizeof(input), stdin);
            //检测是否返回
            if (input[0] == '0' && strlen(input) == 2) { return NULL; }
            ////检测用户是否存在
            user = isUserExist(input);
            if (!user) {
                printf("账号或联系方式错误，请重新输入！\n");
                system("read");
            }
            else { break; }
        }
        //输入密码
        while (true) {
            system("cls");
            printf("请输入账号或联系方式：%s\n", input);
            //输入密码
            printf("请输入密码（输入0重新输入账号）：");
            char password[MaxSize] = { "" };
            fgets(password, sizeof(password), stdin);
            //检测是否重新输入账号
            if (password[0] == '0' && strlen(password) == 2) {
                break;
            }
            //检测密码是否正确
            if (isInputCorrect(user->password, password)) {
                printf("登录成功！\n");
                system("read");
                return user;
            }
            else {
                printf("密码错误，请重新输入！\n");
                system("read");
            }
        }
    }
}
//注册用户账号
void UserSignUp() {
    //创建新用户
    User* temp = (User*)malloc(sizeof(User));
    if (!temp) {
        printf("内存分配失败\n");
        return;
    }
    //初始化账号
    //用户账号
    if (!user_head->next) {
        strcpy(temp->ID, "00000001");
    }
    else {
        strcpy(temp->ID, BuildID(user_head->next->ID));
    }
    temp->level = 1;//用户等级
    temp->total_funding = 0;//总资金
    temp->total_consumption = 0;//总消费
    temp->next = NULL;
    //基本信息
    int flag = 0;
    while (flag != 6) {
        //输入网点名称
        while (!flag) {
            system("cls");
            //输入网点名称
            printf("请输入网点名称(20位以内)(输入0返回用户登录界面)：");
            char name[MaxSize] = { "" };
            fgets(name, sizeof(name), stdin);
            //检测是否返回用户登录界面
            if (name[0] == '0' && strlen(name) == 2) {
                free(temp);
                return;
            }
            //网点名称符合规范，则保存网点名称
            int len = strlen(name);
            if (isStringAllowed(name) && len > 0 && len <= 41) {
                for (int i = 0; name[i] != '\0'; i++) {
                    temp->name[i] = name[i];
                }
                temp->name[len] = '\0';
                flag = 1;
            }
                //网点名称不符合规范，则重新输入
            else {
                printf("网点名称格式错误，请重新输入！\n");
                system("read");
            }
        }
        //设置密码
        while (flag == 1) {
            system("cls");
            printf("请输入网点名称：%s\n", temp->name);
            //输入密码
            printf("请输入密码(需含同时含有大小写字母与数字，且密码为10~20位)(输入0重置网点名称)：");
            char password1[MaxSize] = { "" };
            fgets(password1, sizeof(password1), stdin);
            //检测是否重置网点名称
            if (password1[0] == '0' && strlen(password1) == 2) { flag = 0; break; }
            //检测密码是否符合规范
            if (isPasswordAllowed(password1)) { flag = 2; }
            else {
                printf("密码格式错误，请重新输入！\n");
                system("read");
            }
            //确认密码
            while (flag == 2) {
                system("cls");
                printf("请输入网点名称：%s\n", temp->name);
                printf("请输入密码：%s\n", password1);
                //确认密码
                printf("请确认密码(输入0重新输入密码)：");
                char password2[MaxSize] = { "" };
                fgets(password2, sizeof(password2), stdin);
                //检测是否重新输入密码
                if (password2[0] == '0' && strlen(password2) == 2) { flag = 1; break; }
                //检测两次输入的密码是否一致
                if (isInputCorrect(password1, password2)) {
                    for (int i = 0; password1[i] != '\0'; i++) {
                        temp->password[i] = password1[i];
                    }
                    temp->password[strlen(password1)] = '\0';
                    flag = 3;
                }
                else {
                    printf("两次密码不一致，请重新输入！\n");
                    system("read");
                }
            }
        }
        //输入联系方式
        while (flag == 3) {
            system("cls");
            printf("请输入网点名称：%s\n", temp->name);
            printf("请输入密码：%s\n", temp->password);
            printf("请确认密码：%s\n", temp->password);
            //输入联系方式
            printf("请输入11位手机号码(输入0重置密码)：");
            char Tel[MaxSize] = { "" };
            fgets(Tel, sizeof(Tel), stdin);
            //检测是否重置密码
            if (Tel[0] == '0' && strlen(Tel) == 2) { flag = 1; break; }
            //检测联系方式是否已存在
            if (isUserExist(Tel)) {
                printf("联系方式已经存在，请重新输入！\n");
                system("read");
                continue;
            }
            //联系方式符合规范，则保存联系方式
            if (isNumberAllowed(Tel) && strlen(Tel) == 11) {
                for (int i = 0; Tel[i] != '\0'; i++) {
                    temp->Tel[i] = Tel[i];
                }
                temp->Tel[11] = '\0';
                flag = 4;
            }
                //联系方式不符合规范，则重新输入
            else {
                printf("手机号码格式错误，请重新输入！\n");
                system("read");
            }
        }
        //输入收货地址
        while (flag == 4) {
            system("cls");
            printf("请输入网点名称：%s\n", temp->name);
            printf("请输入密码：%s\n", temp->password);
            printf("请确认密码：%s\n", temp->password);
            printf("请输入11位手机号码：%s\n", temp->Tel);
            //输入收货地址
            printf("请输入收货地址(三十字以内)(输入0重置联系方式)：");
            char address[MaxSize] = { "" };
            fgets(address, sizeof(address), stdin);
            //检测是否重置联系方式
            if (address[0] == '0' && strlen(address) == 2) { flag = 3; break; }
            //收货地址符合规范，则保存收货地址
            int len = strlen(address);
            if (isStringAllowed(address) && len > 0 && len <= 60) {
                for (int i = 0; address[i] != '\0'; i++) {
                    if (address[i] == ' ') { flag = 1; break; }
                    else { temp->address[i] = address[i]; }
                }
                temp->address[len] = '\0';
                flag = 5;
            }
                //收货地址不符合规范，则重新输入
            else {
                printf("收货地址格式错误，请重新输入！\n：");
                system("read");
            }
        }
        //确定创建
        while (flag == 5) {
            system("cls");
            printf("请输入网点名称：%s\n", temp->name);
            printf("请输入密码：%s\n", temp->password);
            printf("请确认密码：%s\n", temp->password);
            printf("请输入11位手机号码：%s\n", temp->Tel);
            printf("请输入收货地址：%s\n", temp->address);
            printf("确认创建账号吗(1是，2否)");
            int result = isSure();
            if (!result) { flag = 6; }
            else if (result == 1) { flag = 4; }
        }
    }
    //加入链表
    temp->next = user_head->next;
    user_head->next = temp;
    //创建完成
    RenewUserFile();
    printf("创建成功！您的账号是%s\n", temp->ID);
    system("read");
}
//忘记密码
void ForgotUserPassword() {
    //查找用户，并验证身份
    User* user = NULL;
    int flag = 0;
    char input[MaxSize] = { "" };
    while (flag != 2) {
        //输入账号或联系方式
        while (!flag) {
            system("cls");
            //输入账号或联系方式
            printf("请输入账号或联系方式(输入0返回)：");
            fgets(input, sizeof(input), stdin);
            //检测是否返回
            if (input[0] == '0' && strlen(input) == 2) { return; }
            //检测结点是否存在
            user = isUserExist(input);
            if (user) { flag = 1; break; }
            else {
                printf("账号或联系方式错误，请重新输入！\n");
                system("read");
            }
        }
        //输入地址，验证身份
        while (flag == 1) {
            system("cls");
            printf("请输入账号或联系方式：%s\n", input);
            printf("请输入收货地址(输入0重新输入账号)：");
            char address[MaxSize] = { "" };
            fgets(address, sizeof(address), stdin);
            //检测是否返回重新输入账号
            if (address[0] == '0' && strlen(address) == 2) { flag = 0; break; }
            //检测收货地址是否正确
            if (isInputCorrect(user->address, address)) { flag = 2; break; }
            else {
                printf("收获地址错误，请重新输入！\n");
                system("read");
            }
        }
    }
    //重置密码
    while (true) {
        system("cls");
        printf("请输入账号或联系方式：%s\n", input);
        printf("请输入收获地址：%s\n", user->address);
        //输入新密码
        printf("请输入新密码(大小写字母与数字，且密码为10~20位)(输入0返回)：");
        char new_password1[MaxSize] = { "" };
        fgets(new_password1, sizeof(new_password1), stdin);
        //检测是否返回用户登录界面
        if (new_password1[0] == '0' && strlen(new_password1) == 2) { return; }
        //检测密码是否符合规范
        if (!isPasswordAllowed(new_password1)) {
            printf("密码不符合规范，请重新输入！\n");
            system("read");
            continue;
        }
        //输入新密码
        while (true) {
            system("cls");
            printf("请输入账号或联系方式：%s\n", input);
            printf("请输入收获地址：%s\n", user->address);
            printf("请输入新密码：%s\n", new_password1);
            //确认密码
            printf("请确认新密码(输入0重新输入新密码)：");
            char new_password2[MaxSize] = { "" };
            fgets(new_password2, sizeof(new_password2), stdin);
            //检测是否重新输入新密码
            if (new_password2[0] == '0' && strlen(new_password2) == 2) { break; }
            //检测两次输入的密码是否一致
            if (isInputCorrect(new_password1, new_password2)) {
                for (int i = 0; new_password1[i] != '\0'; i++) {
                    user->password[i] = new_password1[i];
                }
                user->password[strlen(new_password1)] = '\0';
                //密码重置成功
                RenewUserFile();
                printf("密码重置成功！\n");
                system("read");
                return;
            }
            else {
                printf("两次密码不一致，请重新输入！\n");
                system("read");
            }
        }
    }
}

/*个人信息部分*/
//修改网点名称
void ModifyUserName(User* user) {
    while (true) {
        system("cls");
        //输入新网点名称
        printf("输入新的网点名称(20位以内)(输入0返回)：");
        char new_name[MaxSize] = { "" };
        fgets(new_name, sizeof(new_name), stdin);
        //检测是否返回上一页面
        if (new_name[0] == '0' && strlen(new_name) == 2) { return; }
        //网点名称符合规范，则更新网点名称
        int len = strlen(new_name);
        if (isStringAllowed(new_name) && len > 0 && len <= 40) {
            for (int i = 0; new_name[i] != '\0'; i++) {
                user->name[i] = new_name[i];
            }
            user->name[len] = '\0';
            //修改成功
            RenewUserFile();
            printf("网点名称修改成功！\n");
            system("read");
            return;
        }
            ///网点名称不符合规范，则重新输入
        else {
            printf("网点名称格式错误，请重新输入！\n");
            system("read");
        }
    }
}
//修改收货地址
void ModifyUserAddress(User* user) {
    while (true) {
        system("cls");
        //输入新收货地址
        printf("请输入新收货地址(三十字以内)(输入0返回)：");
        char new_address[MaxSize] = { "" };
        fgets(new_address, sizeof(new_address), stdin);
        //检测是否上一页面
        if (new_address[0] == '0' && strlen(new_address) == 2) { return; }
        //地址符合规范，则更新地址
        int len = strlen(new_address);
        if (isStringAllowed(new_address) && len > 0 && len <= 60) {
            for (int i = 0; new_address[i] != '\0'; i++) {
                user->address[i] = new_address[i];
            }
            user->address[len] = '\0';
            //修改成功
            RenewUserFile();
            printf("地址修改成功！\n");
            system("read");
            return;
        }
            //地址不符合规范，则重新输入
        else {
            printf("收货地址格式错误，请重新输入！\n：");
            system("read");
        }
    }
}
//修改联系方式
void ModifyUserTel(User* user) {
    while (true) {
        system("cls");
        //输入新联系方式
        printf("请输入新的11位手机号码(输入0返回)：");
        char new_Tel[MaxSize] = { "" };
        fgets(new_Tel, sizeof(new_Tel), stdin);
        //检测是否返回上一页面
        if (new_Tel[0] == '0' && strlen(new_Tel) == 2) { return; }
        //检测联系方式是否已存在
        if (isUserExist(new_Tel)) {
            printf("联系方式已经存在，请重新输入！\n");
            system("read");
            continue;
        }
        //联系方式符合规范，则保存联系方式
        if (isNumberAllowed(new_Tel) && strlen(new_Tel) == 11) {
            for (int i = 0; new_Tel[i] != '\0'; i++) {
                user->Tel[i] = new_Tel[i];
            }
            user->Tel[11] = '\0';
            //修改成功
            RenewUserFile();
            printf("修改成功！\n");
            system("read");
            return;
        }
            //错误则重新输入
        else {
            printf("手机号码格式错误，请重新输入！\n");
            system("read");
        }
    }
}
//修改用户密码
void ModifyUserPassword(User* user) {
    //输入密码，检测密码是否正确
    while (true) {
        system("cls");
        printf("账号：%s\n", user->ID);
        //输入密码
        printf("请输入密码（输入0返回）：");
        char password[MaxSize] = { "" };
        fgets(password, sizeof(password), stdin);
        //检测是否返回
        if (password[0] == '0' && strlen(password) == 2) { return; }
        //检测密码是否正确
        if (isInputCorrect(user->password, password)) { break; }
        else {
            printf("密码错误，请重新输入！\n");
            system("read");
        }
    }
    //重置密码
    while (true) {
        system("cls");
        printf("账号：%s\n", user->ID);
        printf("请输入密码：%s\n", user->password);
        //输入新密码
        printf("请输入新密码(需含同时含有大小写字母与数字，且密码为10~20位)(输入0返回)：");
        char new_password1[MaxSize] = { "" };
        fgets(new_password1, sizeof(new_password1), stdin);
        //检测是否返回
        if (new_password1[0] == '0' && strlen(new_password1) == 2) { return; }
            //检测新密码是否规范
        else if (!isPasswordAllowed(new_password1)) {
            printf("密码不符合规范，请重新输入！\n");
            system("read");
            continue;
        }
        //确认新密码
        while (true) {
            system("cls");
            printf("账号：%s\n", user->ID);
            printf("请输入密码：%s\n", user->password);
            printf("请输入新密码：%s\n", new_password1);
            //确认密码
            printf("请确认新密码(输入0重新输入新密码)：");
            char new_password2[MaxSize] = { "" };
            fgets(new_password2, sizeof(new_password2), stdin);
            //检测是否重新输入新密码
            if (new_password2[0] == '0' && strlen(new_password2) == 2) { break; }
            //检测两次输入的密码是否一致
            if (isInputCorrect(new_password1, new_password2)) {
                for (int i = 0; new_password1[i] != '\0'; i++) {
                    user->password[i] = new_password1[i];
                }
                user->password[strlen(new_password1)] = '\0';
                //密码重置成功
                RenewUserFile();
                printf("密码重置成功！\n");
                system("read");
                return;
            }
            else {
                printf("两次密码不一致，请重新输入！\n");
                system("read");
            }
        }
    }
}
//充值余额
void UserRecharge(User* user) {
    while (true) {
        system("cls");
        printf("请输入要充值的金额(十万内的整数)(输入0返回)：");
        char funding[MaxSize] = { "" };
        fgets(funding, sizeof(float ), stdin);
        //检测是否上一页面
        if (funding[0] == '0' && strlen(funding) == 2) { return; }
        //充值金额是否合法，则更新账户余额
        int len = strlen(funding);
        if (isNumberAllowed(funding) && len > 0 && len <= 5) {
            user->total_funding += atoi(funding);
            manager->fund += atoi(funding);
            //余额充值成功
            printf("余额充值成功！\n");
            break;
        }
            //非法输入
        else {
            printf("非法充值，请重新输入！\n");
            system("read");
        }
    }
    //检验用户等级是否提升
    if (user->level == 1) {
        if (user->total_consumption + user->total_funding >= 100000) {
            user->level += 2;
            printf("恭喜您升级为%d级会员！\n", user->level);
        }
        else if (user->total_consumption + user->total_funding >= 10000) {
            user->level += 1;
            printf("恭喜您升级为%d级会员！\n", user->level);
        }
    }
    else if (user->level == 2 && user->total_consumption + user->total_funding >= 100000) {
        user->level += 1;
        printf("恭喜您升级为%d级会员！\n", user->level);
    }
    else if (user->level == 3 && user->total_consumption + user->total_funding >= 500000) {
        user->level += 1;
        printf("恭喜您升级为%d级会员！\n", user->level);
    }
    RenewUserFile();
    RenewManagerFile();
    system("read");
}

/*酒水部分*/
//选择酒水加入购物车
void AddDrinkToTheCart(User* user, Drink* found_drink_head) {
    while (true) {
        system("cls");
        ViewAvailableDrinks(found_drink_head, 1, 0);
        //输	入酒水编号
        printf("请输入要加入购物车的酒水编号(输入0返回)：");
        char drink_ID[MaxSize] = { "" };
        fgets(drink_ID, sizeof(drink_ID), stdin);
        //检验是否返回
        if (drink_ID[0] == '0' && strlen(drink_ID) == 2) { return; }
        //查找酒水
        Drink* drink = isDrinkExist(drink_ID);
        //未找到酒水
        if (!drink->next) {
            printf("未找到酒水，请重新输入！\n");
            system("read");
            continue;
        }
        //找到酒水
        while (true) {
            system("cls");
            ViewAvailableDrinks(drink, 1, 1);
            //输入购买箱数
            printf("请输入要购买箱数(单次不超过十万)(输入0重选酒水)：");
            char nums[MaxSize] = { "" };
            fgets(nums, sizeof(nums), stdin);
            //检验是否重选酒水
            if (nums[0] == '0' && strlen(nums) == 2) { break; }
            //箱数合法，则保存到链表
            if (strlen(nums) && strlen(nums) < 6 && isNumberAllowed(nums)) {
                //更新批发记录
                AddWholesaleRecord(user, drink->next, atoi(nums));
                RenewWholesaleRecordFile();
                //加入成功
                printf("加入成功！\n");
                system("read");
                return;
            }
                //箱数不合法，则重新输入
            else {
                printf("购买箱数错误，请重新输入！\n");
                system("read");
            }
        }
    }
}
//选择酒水直接下单
void PayForDrink(User* user, Drink* head) {
    int flag = 0;
    while (true) {
        //查找酒水
        Drink* drink = NULL;
        char drink_ID[MaxSize] = { "" };
        while (!flag) {
            //查看酒水页面
            system("cls");
            ViewAvailableDrinks(head, 1, 0);
            //输	入酒水编号
            printf("请输入要下单的酒水编号(输入0返回)：");
            fgets(drink_ID, sizeof(drink_ID), stdin);
            //检验是否返回
            if (drink_ID[0] == '0' && strlen(drink_ID) == 2) { return; }
            //查找酒水
            drink = isDrinkExist(drink_ID);
            //未找到酒水
            if (!drink->next) {
                printf("未找到酒水，请重新输入！\n");
                system("read");
            }
                //找到酒水，确认购买箱数
            else { flag = 1; break; }
        }
        //输入购买箱数
        char date[20] = { "" };
        int boxes = 0;
        int gift_boxes = 0;
        while (flag == 1) {
            system("cls");
            ViewAvailableDrinks(drink, 1, 1);
            printf("请输入要购买箱数(单次不超过十万)(输入0重选酒水)：");
            char nums[MaxSize] = { "" };
            fgets(nums, sizeof(nums), stdin);
            //检验是否重选酒水
            if (nums[0] == '0' && strlen(nums) == 2) { flag = 0; break; }
            //箱数合法，则决定下单
            if (strlen(nums) && strlen(nums) < 6 && isNumberAllowed(nums)) {
                //下单时间
                time_t current_time;
                struct tm* time_info;
                time(&current_time);
                time_info = localtime(&current_time);
                strftime(date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
                //优惠
                boxes = atoi(nums);
                gift_boxes = CalculateGiftBoxes(drink->next, date, boxes);
                if (boxes + gift_boxes <= drink->next->stock_quantity) { flag = 2; break; }
            }
            //箱数不合法，则重新输入
            printf("购买箱数错误，请重新输入！\n");
            system("read");
        }
        //是否下单
        float discounted_price = CalculateDiscountedPrice(user, drink->next, date, boxes);
        while (flag == 2) {
            system("cls");
            ViewAvailableDrinks(drink, 1, 1);
            printf("购买箱数：%d\n", boxes);
            printf("赠送%d箱\n", gift_boxes);
            printf("原价：%.2f\n", drink->next->sale_price * boxes);
            printf("优惠后：%.2f\n", discounted_price);
            printf("是否下单(1是，2否)：");
            char select[MaxSize] = { "" };
            fgets(select, sizeof(select), stdin);
            if (select[0] == '1' && strlen(select) == 2) { flag = 3; break; }
            else if (select[0] == '2' && strlen(select) == 2) {
                printf("取消下单！\n");
                system("read");
                return;
            }
            else {
                printf("非法选择，请重新输入！\n");
                system("read");
            }
        }
        //下单
        if (flag == 3) {
            //余额不足
            if (discounted_price > user->total_funding) {
                printf("账户余额不足，请充值！\n");
                system("read");
                return;
            }
            //余额充足
            //更新用户信息
            user->total_funding -= discounted_price;
            user->total_consumption += discounted_price;
            RenewUserFile();
            //更新酒水信息
            drink->next->stock_quantity -= (boxes + gift_boxes);
            RenewDrinkFile();
            //更新批发记录
            RenewWholesaleRecord(user, drink->next, AddWholesaleRecord(user, drink->next, boxes), date);
            RenewWholesaleRecordFile();
            //下单成功
            printf("下单成功！");
            system("read");
            return;
        }
    }
}
//添加批发记录(未下单)
WholesaleRecord* AddWholesaleRecord(User* user, Drink* drink, int boxes) {
    //创建结点
    WholesaleRecord* temp = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
    if (!temp) {
        printf("内存分配失败\n");
        return NULL;
    }
    //订单编号
    if (!wholesaleRecord_head->next) { strcpy(temp->order_number, "0000000001"); }
    else { strcpy(temp->order_number, BuildID(wholesaleRecord_head->next->order_number)); }
    //订单日期
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(temp->date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
    strcpy(temp->user_ID, user->ID);//客户账号
    //酒水信息
    strcpy(temp->past_drink.ID, drink->ID);//酒水编号
    strcpy(temp->past_drink.brand, drink->brand);//酒水品牌
    strcpy(temp->past_drink.taste, drink->taste);//酒水口味
    temp->past_drink.package = drink->package;//包装种类
    strcpy(temp->past_drink.single_bottle_capacity, drink->single_bottle_capacity);//单瓶容量
    strcpy(temp->past_drink.single_box_quantity, drink->single_box_quantity);//单箱数量(单位：瓶/罐)
    temp->past_drink.sale_price = drink->sale_price;//销售价格(单位：元/箱)
    temp->goods_quantity = boxes;//批发数量
    //优惠
    for (int i = 0; i < 3; i++) {
        temp->discount[i].form = 0;//优惠形式
        temp->discount[i].specific_1 = 1;//具体折扣
        for (int j = 0; j < 2; j++) {//具体赠品
            temp->discount[i].specific_2[j] = 0;
        }
        strcpy(temp->discount[i].reason, "无");//优惠原因
    }
    temp->goods_situation = 0;//订单现况
    temp->next = NULL;
    //加入链表
    temp->next = wholesaleRecord_head->next;
    wholesaleRecord_head->next = temp;
    return temp;
}
//计算折扣后价格
float CalculateDiscountedPrice(User* user, Drink* drink, char* current_time, int boxes) {
    float price = drink->sale_price * boxes;
    //因用户等级产生的折扣
    if (user->level == 1) { price *= 1; }
    else if (user->level == 2) { price *= (float)0.95; }
    else if (user->level == 3) { price *= (float)0.90; }
    else { price *= (float)0.85; }
    //因活动产生的折扣
    if (drink->activity.form == 1 && isChronological(drink->activity.date[0], current_time) && isChronological(current_time, drink->activity.date[1])) {
        price *= drink->activity.specific_1;
    }
    return price;
}
//计算赠送箱数
int CalculateGiftBoxes(Drink* drink, char* current_time, int boxes) {
    int gift_boxes = 0;
    if (drink->activity.form == 2 && isChronological(drink->activity.date[0], current_time) && isChronological(current_time, drink->activity.date[1])) {
        gift_boxes = (boxes / drink->activity.specific_2[0]) * drink->activity.specific_2[1];
    }
    return gift_boxes;
}
//更新批发记录(未下单->已下单)
void RenewWholesaleRecord(User* user, Drink* drink, WholesaleRecord* wholesale_record, char* current_time) {
    //酒水信息
    strcpy(wholesale_record->past_drink.ID, drink->ID);//酒水编号
    strcpy(wholesale_record->past_drink.brand, drink->brand);//酒水品牌
    strcpy(wholesale_record->past_drink.taste, drink->taste);//酒水口味
    wholesale_record->past_drink.package = drink->package;//包装种类
    strcpy(wholesale_record->past_drink.single_bottle_capacity, drink->single_bottle_capacity);//单瓶容量
    strcpy(wholesale_record->past_drink.single_box_quantity, drink->single_box_quantity);//单箱数量
    wholesale_record->past_drink.sale_price = drink->sale_price;//销售价格
    //下单时间
    strcpy(wholesale_record->date, current_time);
    //会员优惠
    if (user->level != 1) {
        wholesale_record->discount[0].form = 1;
        strcpy(wholesale_record->discount[0].reason, "会员等级折扣");
        if (user->level == 2) { wholesale_record->discount[0].specific_1 = (float)0.95; }
        else if (user->level == 3) { wholesale_record->discount[0].specific_1 = (float)0.90; }
        else { wholesale_record->discount[0].specific_1 = (float)0.85; }
    }
    //活动优惠
    if (drink->activity.form != 0 && isChronological(drink->activity.date[0], wholesale_record->date) && isChronological(wholesale_record->date, drink->activity.date[1])) {
        wholesale_record->discount[1].form = drink->activity.form;
        wholesale_record->discount[1].specific_1 = drink->activity.specific_1;
        for (int i = 0; i < 2; i++) {
            wholesale_record->discount[1].specific_2[i] = drink->activity.specific_2[i];
        }
        strcpy(wholesale_record->discount[1].reason, drink->activity.reason);
    }
    //订单状态
    wholesale_record->goods_situation = 1;
}


/*购物车部分*/
//创建用户购物车链表
WholesaleRecord* CreatUserShoppingCartList(User* user) {
    //创建哨兵结点
    WholesaleRecord* head = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
    WholesaleRecord* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    //寻找批发记录链表中的购物车结点
    WholesaleRecord* wholesale_record = wholesaleRecord_head->next;
    while (wholesale_record) {
        if (!wholesale_record->goods_situation && isInputCorrect(wholesale_record->user_ID, user->ID)) {
            WholesaleRecord* temp = CreatTempWholesaleRecordListNode(wholesale_record);
            tail->next = temp;
            tail = temp;
        }
        wholesale_record = wholesale_record->next;
    }
    return head;
}
//查看用户购物车
void ViewUserShoppingCart(User* user, WholesaleRecord* cart_head, int type) {
    //查看时间
    char date[20] = { "" };
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
    //查看购物车
    WholesaleRecord* wholesale_record = cart_head->next;
    printf("订单\n");
    printf("*********************************\n");
    while (wholesale_record) {
        Drink* drink = isDrinkExist(wholesale_record->past_drink.ID);
        printf("*订单号：%s\n", wholesale_record->order_number);
        if (!drink->next) { printf("酒水下架，订单失效\n"); }
        else {
            ViewAvailableDrinks(drink, 1, 1);
            printf(" 购买箱数：%d\n", wholesale_record->goods_quantity);
            printf(" 赠送%d箱\n", CalculateGiftBoxes(drink->next, date, wholesale_record->goods_quantity));
            printf(" 原价：%.2f\n", drink->next->sale_price * wholesale_record->goods_quantity);
            printf(" 优惠后：%.2f\n\n", CalculateDiscountedPrice(user, drink->next, date, wholesale_record->goods_quantity));
        }
        wholesale_record = wholesale_record->next;
        if (type == 1) { break; }
    }
    printf("*********************************\n");
}
//修改订单
void UserModifyAnOrder(User* user, WholesaleRecord* cart_head) {
    //查询订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        else if (!wholesale_record->next || !isInputCorrect(wholesale_record->next->user_ID, user->ID) || wholesale_record->next->goods_situation) {
            wholesale_record = NULL;
            printf("订单错误！请重新输入！\n");
            system("read");
        }
        else { break; }
    }
    //寻找订单中的酒水
    Drink* drink = isDrinkExist(wholesale_record->next->past_drink.ID);
    //修改订单
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, wholesale_record, 1);
        printf("请输入要购买箱数(输入0重选订单)：");
        char nums[MaxSize] = { "" };
        fgets(nums, sizeof(nums), stdin);
        //检验是否重选订单
        if (nums[0] == '0' && strlen(nums) == 2) { return; }
        //箱数合法，则保存
        if (strlen(nums) && strlen(nums) < 6 && isNumberAllowed(nums)) {
            //更新批发记录
            wholesale_record->next->goods_quantity = atoi(nums);
            RenewWholesaleRecordFile();
            //加入成功
            printf("修改成功！\n");
            system("read");
            return;
        }
            //箱数不合法，则重新输入
        else {
            printf("购买箱数错误，请重新输入！\n");
            system("read");
        }
    }
}
//选择订单下单
void PayForAnOrder(User* user, WholesaleRecord* cart_head) {
    //查询订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        if (!wholesale_record->next || !isInputCorrect(wholesale_record->next->user_ID, user->ID) || wholesale_record->next->goods_situation) {
            printf("订单不存在！请重新输入！\n");
            system("read");
        }
        else { break; }
    }
    //下单时间
    char date[20] = { "" };
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
    //寻找订单中的酒水
    Drink* drink = isDrinkExist(wholesale_record->next->past_drink.ID);
    //优惠
    float discounted_price = CalculateDiscountedPrice(user, drink->next, date, wholesale_record->next->goods_quantity);
    int gift_boxes = CalculateGiftBoxes(drink->next, date, wholesale_record->next->goods_quantity);
    //确认下单
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, wholesale_record, 1);
        printf("是否下单(1是，2否)：");
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //酒水库存不足
    if (wholesale_record->next->goods_quantity + gift_boxes > drink->next->stock_quantity) {
        printf("酒水库存不足！\n");
        system("read");
        return;
    }
    //账户余额不足
    if (discounted_price > user->total_funding) {
        printf("账户余额不足！\n");
        system("read");
        return;
    }
    //下单成功
    //更新用户信息
    user->total_funding -= discounted_price;
    user->total_consumption += discounted_price;
    RenewUserFile();
    //更新酒水信息
    drink->next->stock_quantity -= (wholesale_record->next->goods_quantity + gift_boxes);
    RenewDrinkFile();
    //更新批发记录
    RenewWholesaleRecord(user, drink->next, wholesale_record->next, date);
    RenewWholesaleRecordFile();
    printf("下单成功！");
    system("read");
}
//全选下单
void PayForAllOrder(User* user, WholesaleRecord* cart_head) {
    //确定下单
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        printf("确定下单购物车中所有商品吗(1是，2否)：");
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //下单时间
    char date[20] = { "" };
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
    //计算费用与酒水库存
    float total_price = 0;//下单总费用
    WholesaleRecord* wholesale_record = wholesaleRecord_head->next;
    while (wholesale_record) {
        if (!wholesale_record->goods_situation && isInputCorrect(wholesale_record->user_ID, user->ID)) {
            Drink* drink = isDrinkExist(wholesale_record->past_drink.ID)->next;
            int gift_boxes = CalculateGiftBoxes(drink, date, wholesale_record->goods_quantity);
            //库存不足，则直接返回
            if (drink->stock_quantity < wholesale_record->goods_quantity + gift_boxes) {
                printf("编号为“%s”的酒水库存不足！\n", drink->ID);
                system("read");
                return;
            }
            //库存充足，则计算费用
            total_price += CalculateDiscountedPrice(user, drink, date, wholesale_record->goods_quantity);
        }
        wholesale_record = wholesale_record->next;
    }
    //余额不足
    if (total_price > user->total_funding) {
        printf("账户余额不足，请充值！\n");
        system("read");
        return;
    }
    //余额充足
    //更新用户信息
    user->total_funding -= total_price;
    user->total_consumption += total_price;
    RenewUserFile(user_head);
    //更新酒水信息与批发记录
    wholesale_record = wholesaleRecord_head->next;
    while (wholesale_record) {
        if (!wholesale_record->goods_situation && isInputCorrect(wholesale_record->user_ID, user->ID)) {
            Drink* drink = isDrinkExist(wholesale_record->past_drink.ID)->next;
            //更新酒水库存
            int gift_boxes = CalculateGiftBoxes(drink, date, wholesale_record->goods_quantity);
            drink->stock_quantity -= (wholesale_record->goods_quantity + gift_boxes);
            //更新批发记录
            RenewWholesaleRecord(user, drink, wholesale_record, date);
        }
        wholesale_record = wholesale_record->next;
    }
    RenewDrinkFile();
    RenewWholesaleRecordFile();
    //下单成功
    printf("下单成功！");
    system("read");
}
//从购物车中删除订单
void DeleteAnOrder(User* user, WholesaleRecord* cart_head) {
    //查询订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        if (!wholesale_record->next || !isInputCorrect(wholesale_record->next->user_ID, user->ID) || wholesale_record->next->goods_situation) {
            printf("订单不存在！请重新输入！\n");
            system("read");
        }
        else { break; }
    }
    //确认删除
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, wholesale_record, 1);
        printf("确定要删除此订单吗(1是，2否)：");
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //删除批发记录链表中的结点
    WholesaleRecord* temp = wholesale_record->next;
    wholesale_record->next = temp->next;
    free(temp);
    temp = NULL;
    RenewWholesaleRecordFile();
    printf("删除成功！\n");
    system("read");
}
//清空购物车
void clsShoppingCart(User* user, WholesaleRecord* cart_head) {
    //确认清空
    while (true) {
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        printf("购物车清空后无法恢复(1是，2否)！\n");
        printf("请输入您的选择：");
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //清空对应批发记录链表
    WholesaleRecord* wholesale_record = wholesaleRecord_head;
    while (wholesale_record->next) {
        if (!wholesale_record->next->goods_situation && isInputCorrect(wholesale_record->next->user_ID, user->ID)) {
            WholesaleRecord* temp = wholesale_record->next;
            wholesale_record->next = temp->next;
            free(temp);
        }
        else { wholesale_record = wholesale_record->next; }
    }
    RenewWholesaleRecordFile();
    printf("清空成功！\n");
    system("read");
}

/*批发记录部分*/
//申请退货
void UserApplicationForReturn(User* user, WholesaleRecord* head) {
    //查找订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("cls");
        ViewWholesaleRecords(head, user, 6, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        else if (!wholesale_record->next || !isInputCorrect(wholesale_record->next->user_ID, user->ID) || !wholesale_record->next->goods_situation) {
            printf("未找到订单，请重新输入！\n");
            system("read");
        }
        else { break; }
    }
    //是否退货
    while (true) {
        system("cls");
        ViewWholesaleRecords(wholesale_record, user, 6, 1);
        printf("是否确认退货(1是，2否)：");
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //退货
    wholesale_record->next->goods_situation = 4;
    RenewWholesaleRecordFile();
    printf("已申请退货！\n");
    system("read");
}
//输入查询条件
int UserInputWholesaleRecordConditions(char* date, char* situation, char* brand, char* taste, char* package, char* capacity) {
    int flag = 0;
    while (true) {
        system("cls");
        if (flag > 0) { printf("请输入订单日期：%s\n", date); }
        if (flag > 1) { printf("请输入订单现状(1已下单，2派送中，3已到货，4申请退货，5已退货，6不限)：%c\n", situation[0]); }
        if (flag > 2) { printf("请输入品牌：%s\n", brand); }
        if (flag > 3) { printf("请输入口味：%s\n", taste); }
        if (flag > 4) { printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]); }
        if (flag > 5) { printf("请输入单瓶容量：%s\n", capacity); }
        //订单日期
        while (!flag) {
            printf("请输入订单日期(xxxx-xx-xx)(无需直接回车)(输入0返回)：");
            fgets(date, sizeof(date), stdin);
            if (date[0] == '0' && strlen(date) == 2) { return 0; }
            else { flag = 1; }
        }
        //订单现状
        while (flag == 1) {
            printf("请输入订单现状(1已下单，2派送中，3已到货，4申请退货，5已退货，6不限)(输入0重选订单日期)：");
            int result = isSituationCorrect(situation);
            if (!result) { flag = 0; }
            else if (result == 1) { flag = 2; }
            else { break; }
        }
        //酒水品牌
        while (flag == 2) {
            printf("请输入品牌(无需直接回车)(输入0重选订单现状)：");
            fgets(brand, sizeof(brand), stdin);
            if (brand[0] == '0' && strlen(brand) == 2) { flag = 1; }
            else { flag = 3; }
        }
        //酒水口味
        while (flag == 3) {
            printf("请输入口味(无需直接回车)(输入0重选品牌)：");
            fgets(taste, sizeof(taste), stdin);
            if (taste[0] == '0' && strlen(taste) == 2) { flag = 2; }
            else { flag = 4; }
        }
        //包装种类
        while (flag == 4) {
            printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)(输入0重选口味)：");
            int result = isPackageCorrect(package, 1);
            if (!result) { flag = 3; }
            else if (result == 1) { flag = 5; }
            else { break; }
        }
        //单瓶容量
        while (flag == 5) {
            printf("请输入单瓶容量mL(无需直接回车)(输入0重选包装)：");
            fgets(capacity, sizeof(capacity), stdin);
            if (capacity[0] == '0' && strlen(capacity) == 2) { flag = 4; }
            else { flag = 6; }
        }
        //确定设置完成
        while (flag == 6) {
            printf("是否确定搜索(1是，2否)：");
            int result = isSure();
            if (!result) { return 1; }
            else if (result == 1) { flag = 5; }
            else { break; }
        }
    }
}
//创建查询批发记录链表
WholesaleRecord* CreatUserFoundWholesaleRecordList(char* date, char* situation, char* brand, char* taste, char* package, char* capacity) {
    //创建哨兵结点
    WholesaleRecord* head = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
    WholesaleRecord* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    //寻找批发记录
    WholesaleRecord* wholesale_record = wholesaleRecord_head->next;
    while (wholesale_record) {
        ///寻找满足条件的批发记录
        //检验订单日期
        if (strlen(date) != 0 && !isInclude(wholesale_record->date, date)) { wholesale_record = wholesale_record->next; continue; }
        //检验订单状态
        if (situation[0] != '6' && wholesale_record->goods_situation != (package[0] - '0')) { wholesale_record = wholesale_record->next; continue; }
        //检验包装种类
        if (package[0] != '4' && wholesale_record->past_drink.package != (package[0] - '0')) { wholesale_record = wholesale_record->next; continue; }
        //检验容量
        if (strlen(capacity) != 0 && !isInputCorrect(wholesale_record->past_drink.single_bottle_capacity, capacity)) { wholesale_record = wholesale_record->next; continue; }
        //检验品牌
        if (strlen(brand) != 0 && !isInclude(wholesale_record->past_drink.brand, brand)) { wholesale_record = wholesale_record->next; continue; }
        //检验口味
        if (strlen(taste) != 0 && !isInclude(wholesale_record->past_drink.taste, taste)) { wholesale_record = wholesale_record->next; continue; }
        ///创建结点
        WholesaleRecord* temp = CreatTempWholesaleRecordListNode(wholesale_record);
        tail->next = temp;
        tail = temp;
        wholesale_record = wholesale_record->next;
    }
    return head;
}
//(郗)**********************************************************