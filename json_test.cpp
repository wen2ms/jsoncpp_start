#include <json/json.h>

#include <fstream>
#include <iostream>

/*
[
    "luffy", 19, 170, false,
    ["ace", "sabo"],
    {"sex":"man", "girlfriend":"Hanhcock"}
]
*/

void write_json() {
    Json::Value root;

    root.append("luffy");
    root.append(19);
    root.append(170);
    root.append(false);

    Json::Value sub_array;
    sub_array.append("ace");
    sub_array.append("sabo");
    root.append(sub_array);

    Json::Value object;
    object["sex"] = "man";
    object["girlfriend"] = "Hanhcock";
    root.append(object);

    // Json::FastWriter writer;
    // std::string json = writer.write(root);
    std::string json = root.toStyledString();

    std::ofstream outfile("test.json");
    outfile << json;
    outfile.close();
}

void read_json() {
    std::ifstream infile("test.json");
    Json::Reader reader;
    Json::Value root;

    reader.parse(infile, root);
    if (root.isArray()) {
        for (int i = 0; i < root.size(); ++i) {
            Json::Value item = root[i];
            if (item.isInt()) {
                std::cout << item.asInt() << ", ";
            } else if (item.isString()) {
                std::cout << item.asString() << ", ";
            } else if (item.isBool()) {
                std::cout << item.asBool() << ", ";
            } else if (item.isArray()) {
                for (int j = 0; j < item.size(); ++j) {
                    std::cout << item[j].asString() << ", ";
                }
            } else if (item.isObject()) {
                Json::Value::Members keys = item.getMemberNames();
                for (int j = 0; j < keys.size(); ++j) {
                    std::cout << keys.at(j) << ":" << item[keys[j]].asString() << ",";
                }
            }
            std::cout << std::endl;
        }
    } else if (root.isObject()) {

    }
}

int main() {
    write_json();
    read_json();

    return 0;
}