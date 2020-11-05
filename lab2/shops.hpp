//
//  shops.hpp
//  shops
//
//  Created by Sara Nikolić on 28.09.2020.
//  Copyright © 2020 Sara Nikolić. All rights reserved.
//

#ifndef shops_hpp
#define shops_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <map>
#include <algorithm>

class Product{
private:
    static int prodID;
    int productID;
    std::string prodName;
public:
    Product();
    Product(const std::string& prodName);

    int getProdID() const;
    std::string getProdName() const;

//    ~Product();
};

class Records{
private:
    int productID;
    int amount;
    int price;
public:
    Records();
    ~Records();
    Records(int productID, int amount, int price);
    
    int getRecordsID() const;
    int getPrice() const;
    int getAmount() const;
    void setPrice(int _price);
    void setAmount(int _amount);
    void decrementAmount();
    void incrementAmount();
};

class Shop{
private:
    static int shopID;
    int shoppingID;
    std::string shopName;
    std::string address;
    std::map<int,Records> prods_shop;
public:
    Shop();
    Shop(std::string shopName, std::string address);
    
    int getShopID() const;
    std::string getAddress() const;
    std::string getShopName() const;
    std::map<int,Records> getProds_Shop() const;
    
    void putProduct(int productID, int amount, int price); // 3 - put product in a shop
    void possibleBuying(int sum); // 5 - imaginative buying
    int buy(int productID, int amount); // 6 - buying
    int sumofVector(std::vector<Records> partija); // 7 - shop with the least price of products
    
    // needed functions
    void printProds_Shop();
    bool isProds_Shop(int prodID);
    bool is_ProdIDinShop(int prodID);
    int Price(int prodID);
    int is_PriceinShop(int prodID);
    //    ~Shop();
};

class Functional{
private:
    std::map<int, Shop> shops;
    std::map<int, Product> products;
public:
    Functional();
    ~Functional();
    
    void makeProd(const std::string& prodName); // 1 - making new product
    void makeShop(const std::string& shopName, const std::string& address); // 2 - making new shop
    void putProductinShop(Records rec, int shopID); // 3.1 - putting one product into a certain shop
    void putProductsinShop(std::vector<Records> prods, int shopID); // 3.2 - putting the group of products into a certain shop
    std::pair<int, std::string> CheapestProduct(int productID); // 4 - finding a shop with the cheapest price of a certain product
    void ProductsforSum(int shopID, int sum); // 5 - possible buying of products, for a certain sum from a certain shop (not actually buying!)
    int buyingProducts(std::map<int,int> list, int shopID); // 6 - buying a list of products from a certain shop
    std::pair<int,std::string> shopProducts(std::vector<Records> partija); // 7 - finding a shop with the cheapest price of a list of products
    
    // needed functions
    std::string getProdName(int prodID) const;
    std::string getShopName(int shopID) const;
    bool productExists(int prodID);
    bool productExistsinShop(int prodID, int shopID);
    bool shopExists(int shopID);
};

#endif /* shops_hpp */
