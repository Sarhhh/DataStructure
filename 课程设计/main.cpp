#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// ==================== 结构体定义 ====================

struct ManufacturerInfo
{
    string ID;      // 厂家编号
    string Name;    // 生产厂家名称
    string Address; // 地址
    string Contact; // 联系人
    string Phone;   // 电话
};

struct ProductInfo
{
    string Type;           // 物品种类：口罩/手套/防护服
    string ManufacturerID; // 厂家编号
    int Count;             // 数量
    double Price;          // 单价（元）
    string ReceiveDate;    // 收到日期
    string Contact;        // 联系人
    string Phone;          // 电话
};

struct ReceivingUnitInfo
{
    string ID;      // 单位编号
    string Name;    // 接收单位名称
    string Address; // 地址
    string Contact; // 联系人
    string Phone;   // 电话
};

struct ReceivingInfo
{
    string UnitID;           // 接收单位编号
    string ProductType;      // 物品种类
    int Count;               // 数量
    string DistributionDate; // 发放日期
    string ManufacturerID;   // 厂家编号
    bool IsReceived;         // 是否收到
};

// ==================== 初始化模拟数据 ====================

void initData(
    vector<ManufacturerInfo> &manufacturers,
    vector<ProductInfo> &products,
    vector<ReceivingUnitInfo> &units,
    vector<ReceivingInfo> &receivings)
{
    // ---- 生产商信息（4条）----
    manufacturers = {
        {"MF001", "蓝天医疗用品有限公司", "北京市朝阳区建国路100号", "张三", "010-8888-0001"},
        {"MF002", "长江防护设备有限公司", "上海市浦东新区陆家嘴200号", "李四", "021-6666-0002"},
        {"MF003", "黄河医材集团有限公司", "广州市天河区体育西路300号", "王五", "020-3333-0003"},
        {"MF004", "泰山卫生材料厂", "武汉市武昌区中南路400号", "赵六", "027-2222-0004"}};

    // ---- 物资信息（捐赠入库记录，共24条，≥20条）----
    // 每个厂家分多次捐赠3种物资
    products = {
        // MF001 蓝天医疗 的捐赠
        {"口罩", "MF001", 1000, 2.50, "2024-01-15", "张三", "010-8888-0001"},
        {"手套", "MF001", 800, 1.80, "2024-01-15", "张三", "010-8888-0001"},
        {"防护服", "MF001", 500, 45.00, "2024-01-20", "张三", "010-8888-0001"},
        {"口罩", "MF001", 1500, 2.50, "2024-02-10", "张三", "010-8888-0001"},
        {"手套", "MF001", 1200, 1.80, "2024-02-10", "张三", "010-8888-0001"},
        {"防护服", "MF001", 300, 45.00, "2024-02-15", "张三", "010-8888-0001"},
        // MF002 长江防护 的捐赠
        {"口罩", "MF002", 2000, 2.80, "2024-01-18", "李四", "021-6666-0002"},
        {"手套", "MF002", 1500, 2.00, "2024-01-18", "李四", "021-6666-0002"},
        {"防护服", "MF002", 600, 50.00, "2024-01-25", "李四", "021-6666-0002"},
        {"口罩", "MF002", 1800, 2.80, "2024-02-20", "李四", "021-6666-0002"},
        {"手套", "MF002", 1000, 2.00, "2024-02-20", "李四", "021-6666-0002"},
        {"防护服", "MF002", 400, 50.00, "2024-03-01", "李四", "021-6666-0002"},
        // MF003 黄河医材 的捐赠
        {"口罩", "MF003", 3000, 2.20, "2024-01-22", "王五", "020-3333-0003"},
        {"手套", "MF003", 2000, 1.60, "2024-01-22", "王五", "020-3333-0003"},
        {"防护服", "MF003", 800, 55.00, "2024-01-30", "王五", "020-3333-0003"},
        {"口罩", "MF003", 2500, 2.20, "2024-02-28", "王五", "020-3333-0003"},
        {"手套", "MF003", 1800, 1.60, "2024-02-28", "王五", "020-3333-0003"},
        {"防护服", "MF003", 350, 55.00, "2024-03-10", "王五", "020-3333-0003"},
        // MF004 泰山卫生 的捐赠
        {"口罩", "MF004", 1200, 2.40, "2024-01-28", "赵六", "027-2222-0004"},
        {"手套", "MF004", 900, 1.85, "2024-01-28", "赵六", "027-2222-0004"},
        {"防护服", "MF004", 450, 47.00, "2024-02-05", "赵六", "027-2222-0004"},
        {"口罩", "MF004", 1600, 2.40, "2024-03-05", "赵六", "027-2222-0004"},
        {"手套", "MF004", 1100, 1.85, "2024-03-05", "赵六", "027-2222-0004"},
        {"防护服", "MF004", 280, 47.00, "2024-03-12", "赵六", "027-2222-0004"}};

    // ---- 接收单位信息（8条）----
    units = {
        {"RU001", "B市第一人民医院", "B市解放路10号", "陈医生", "0510-1111-1001"},
        {"RU002", "B市传染病防治中心", "B市健康路20号", "刘主任", "0510-2222-1002"},
        {"RU003", "C市中心医院", "C市人民路30号", "黄护士", "0511-3333-1003"},
        {"RU004", "C市紧急救援中心", "C市平安路40号", "周科长", "0511-4444-1004"},
        {"RU005", "D市第一人民医院", "D市长城路50号", "吴院长", "0512-5555-1005"},
        {"RU006", "D市社区卫生服务中心", "D市团结路60号", "郑主任", "0512-6666-1006"},
        {"RU007", "E市人民医院", "E市光明路70号", "孙医生", "0513-7777-1007"},
        {"RU008", "E市疾控中心", "E市胜利路80号", "马科长", "0513-8888-1008"}};

    // ---- 接收信息（发放记录，8单位 × 3种 = 24条）----
    receivings = {
        {"RU001", "口罩", 500, "2024-03-01", "MF001", true},
        {"RU001", "手套", 400, "2024-03-01", "MF001", true},
        {"RU001", "防护服", 200, "2024-03-02", "MF002", true},
        {"RU002", "口罩", 600, "2024-03-03", "MF003", true},
        {"RU002", "手套", 350, "2024-03-03", "MF002", true},
        {"RU002", "防护服", 180, "2024-03-04", "MF001", false},
        {"RU003", "口罩", 700, "2024-03-05", "MF002", true},
        {"RU003", "手套", 500, "2024-03-05", "MF004", true},
        {"RU003", "防护服", 250, "2024-03-06", "MF003", true},
        {"RU004", "口罩", 450, "2024-03-07", "MF004", true},
        {"RU004", "手套", 300, "2024-03-07", "MF003", false},
        {"RU004", "防护服", 150, "2024-03-08", "MF001", true},
        {"RU005", "口罩", 800, "2024-03-09", "MF001", true},
        {"RU005", "手套", 550, "2024-03-09", "MF002", true},
        {"RU005", "防护服", 220, "2024-03-10", "MF004", true},
        {"RU006", "口罩", 350, "2024-03-11", "MF003", true},
        {"RU006", "手套", 280, "2024-03-11", "MF001", true},
        {"RU006", "防护服", 120, "2024-03-12", "MF002", false},
        {"RU007", "口罩", 900, "2024-03-13", "MF004", true},
        {"RU007", "手套", 600, "2024-03-13", "MF002", true},
        {"RU007", "防护服", 300, "2024-03-14", "MF003", true},
        {"RU008", "口罩", 400, "2024-03-15", "MF001", true},
        {"RU008", "手套", 320, "2024-03-15", "MF004", true},
        {"RU008", "防护服", 160, "2024-03-16", "MF002", true}};
}

// ==================== 打印表格（列右对齐）====================

void printManufacturers(const vector<ManufacturerInfo> &list)
{
    cout << "\n┌──────────┬──────────────────────────┬──────────────────────────────┬────────────┬──────────────────┐\n";
    cout << "│" << right << setw(10) << "厂家编号"
         << "│" << setw(26) << "生产厂家名称"
         << "│" << setw(30) << "地址"
         << "│" << setw(12) << "联系人"
         << "│" << setw(18) << "电话" << "│\n";
    cout << "├──────────┼──────────────────────────┼──────────────────────────────┼────────────┼──────────────────┤\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << "│" << right << setw(10) << list[i].ID
             << "│" << setw(26) << list[i].Name
             << "│" << setw(30) << list[i].Address
             << "│" << setw(12) << list[i].Contact
             << "│" << setw(18) << list[i].Phone << "│\n";
    }
    cout << "└──────────┴──────────────────────────┴──────────────────────────────┴────────────┴──────────────────┘\n";
}

void printProducts(const vector<ProductInfo> &list)
{
    cout << "\n┌──────┬────────┬──────────┬──────┬──────────┬──────────────┬──────────┬────────────────────┐\n";
    cout << "│" << right << setw(6) << "序号"
         << "│" << setw(8) << "种类"
         << "│" << setw(10) << "厂家编号"
         << "│" << setw(6) << "数量"
         << "│" << setw(10) << "单价(元)"
         << "│" << setw(14) << "收到日期"
         << "│" << setw(10) << "联系人"
         << "│" << setw(20) << "电话" << "│\n";
    cout << "├──────┼────────┼──────────┼──────┼──────────┼──────────────┼──────────┼────────────────────┤\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << "│" << right << setw(6) << (i + 1)
             << "│" << setw(8) << list[i].Type
             << "│" << setw(10) << list[i].ManufacturerID
             << "│" << setw(6) << list[i].Count
             << "│" << setw(10) << fixed << setprecision(2) << list[i].Price
             << "│" << setw(14) << list[i].ReceiveDate
             << "│" << setw(10) << list[i].Contact
             << "│" << setw(20) << list[i].Phone << "│\n";
    }
    cout << "└──────┴────────┴──────────┴──────┴──────────┴──────────────┴──────────┴────────────────────┘\n";
}

void printReceivingUnits(const vector<ReceivingUnitInfo> &list)
{
    cout << "\n┌──────────┬──────────────────────────┬──────────────────────────────┬────────────┬──────────────────┐\n";
    cout << "│" << right << setw(10) << "单位编号"
         << "│" << setw(26) << "接收单位名称"
         << "│" << setw(30) << "地址"
         << "│" << setw(12) << "联系人"
         << "│" << setw(18) << "电话" << "│\n";
    cout << "├──────────┼──────────────────────────┼──────────────────────────────┼────────────┼──────────────────┤\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << "│" << right << setw(10) << list[i].ID
             << "│" << setw(26) << list[i].Name
             << "│" << setw(30) << list[i].Address
             << "│" << setw(12) << list[i].Contact
             << "│" << setw(18) << list[i].Phone << "│\n";
    }
    cout << "└──────────┴──────────────────────────┴──────────────────────────────┴────────────┴──────────────────┘\n";
}

void printReceivings(const vector<ReceivingInfo> &list)
{
    cout << "\n┌──────┬──────────┬──────────┬──────┬──────────────┬──────────┬──────────┐\n";
    cout << "│" << right << setw(6) << "序号"
         << "│" << setw(10) << "单位编号"
         << "│" << setw(10) << "种类"
         << "│" << setw(6) << "数量"
         << "│" << setw(14) << "发放日期"
         << "│" << setw(10) << "厂家编号"
         << "│" << setw(10) << "是否收到" << "│\n";
    cout << "├──────┼──────────┼──────────┼──────┼──────────────┼──────────┼──────────┤\n";
    for (int i = 0; i < list.size(); i++)
    {
        cout << "│" << right << setw(6) << (i + 1)
             << "│" << setw(10) << list[i].UnitID
             << "│" << setw(10) << list[i].ProductType
             << "│" << setw(6) << list[i].Count
             << "│" << setw(14) << list[i].DistributionDate
             << "│" << setw(10) << list[i].ManufacturerID
             << "│" << setw(10) << (list[i].IsReceived ? "是" : "否") << "│\n";
    }
    cout << "└──────┴──────────┴──────────┴──────┴──────────────┴──────────┴──────────┘\n";
}

void printAllTables(
    const vector<ManufacturerInfo> &manufacturers,
    const vector<ProductInfo> &products,
    const vector<ReceivingUnitInfo> &units,
    const vector<ReceivingInfo> &receivings)
{
    printManufacturers(manufacturers);
    printProducts(products);
    printReceivingUnits(units);
    printReceivings(receivings);
}

// ==================== 文件存储 ====================

void saveToFile(
    const vector<ManufacturerInfo> &manufacturers,
    const vector<ProductInfo> &products,
    const vector<ReceivingUnitInfo> &units,
    const vector<ReceivingInfo> &receivings)
{
    ofstream file("aid_data.txt");
    if (!file)
    {
        cerr << "无法打开文件！\n";
        return;
    }
    // 用 | 作为字段分隔符，方便人读也方便解析
    file << "=== 生产商信息 ===\n";
    for (int i = 0; i < manufacturers.size(); i++)
        file << manufacturers[i].ID << "|" << manufacturers[i].Name << "|" << manufacturers[i].Address << "|"
             << manufacturers[i].Contact << "|" << manufacturers[i].Phone << "\n";

    file << "=== 物资信息 ===\n";
    for (int i = 0; i < products.size(); i++)
        file << products[i].Type << "|" << products[i].ManufacturerID << "|" << products[i].Count << "|"
             << products[i].Price << "|" << products[i].ReceiveDate << "|"
             << products[i].Contact << "|" << products[i].Phone << "\n";

    file << "=== 接收单位信息 ===\n";
    for (int i = 0; i < units.size(); i++)
        file << units[i].ID << "|" << units[i].Name << "|" << units[i].Address << "|"
             << units[i].Contact << "|" << units[i].Phone << "\n";

    file << "=== 接收信息 ===\n";
    for (int i = 0; i < receivings.size(); i++)
        file << receivings[i].UnitID << "|" << receivings[i].ProductType << "|" << receivings[i].Count << "|"
             << receivings[i].DistributionDate << "|" << receivings[i].ManufacturerID << "|"
             << (receivings[i].IsReceived ? "1" : "0") << "\n";

    file.close();
    cout << "\n数据已保存到 aid_data.txt\n";
}

// ==================== 主菜单 ====================

int main()
{
    vector<ManufacturerInfo> manufacturers;
    vector<ProductInfo> products;
    vector<ReceivingUnitInfo> units;
    vector<ReceivingInfo> receivings;

    initData(manufacturers, products, units, receivings);

    int choice;
    do
    {
        printf("\n");
        printf("╭──────────────────────────────────────────────────────╮\n");
        printf("│                  援助物资分发系统                    │\n");
        printf("├──────────────────────────────────────────────────────┤\n");
        printf("│               [1]   打印所有表格                     │\n");
        printf("│               [2]   查询厂家累计捐赠总价值           │\n");
        printf("│               [3]   物资分类排序                     │\n");
        printf("│               [4]   最短运输路径                     │\n");
        printf("│               [5]   二叉树遍历                       │\n");
        printf("│               [6]   保存数据到文件                   │\n");
        printf("│               [0]   退出系统                         │\n");
        printf("╰──────────────────────────────────────────────────────╯\n");
        printf("请选择: ");
        cin >> choice;

        switch (choice)
        {
        case 1:
            printAllTables(manufacturers, products, units, receivings);
            break;
        case 6:
            saveToFile(manufacturers, products, units, receivings);
            break;
        case 0:
            printf("再见！\n");
            break;
        default:
            cout << "该功能尚未实现。\n";
            break;
        }
    } while (choice != 0);

    return 0;
}