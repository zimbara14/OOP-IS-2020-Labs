//
//  shops.cpp
//  shops
//
//  Created by Sara Nikolić on 28.09.2020.
//  Copyright © 2020 Sara Nikolić. All rights reserved.
//

#include "shops.hpp"
#include <map>
#include <vector>
#include <utility>

int Product::prodID = 0;

Product::Product(){}

Product::Product(const std::string& prodName){
    this->prodName = prodName;
    this->productID = ++prodID;
}

int Product::getProdID() const{
    return productID;
}

std::string Product::getProdName() const{
    return prodName;
}

Records::Records(){}

Records::~Records(){}

Records::Records(int productID, int amount, int price){
    this->productID = productID;
    this->amount = amount;
    this->price = price;
}

int Records::getRecordsID() const{
    return productID;
}

int Records::getPrice() const{
    return price;
}

int Records::getAmount() const{
    return amount;
}

void Records::setPrice(int _price){
    price = _price;
}

void Records::setAmount(int _amount){
    amount = _amount;
}

void Records::incrementAmount(){
    ++amount;
}

void Records::decrementAmount(){
    --amount;
}

int Shop::shopID = 0;

Shop::Shop(){}

Shop::Shop(std::string shopName, std::string address){
    this->shoppingID = ++shopID;
    this->shopName = shopName;
    this->address = address;
}

int Shop::getShopID() const{
    return shoppingID;
}

std::string Shop::getAddress() const{
    return address;
}

std::string Shop::getShopName() const{
    return shopName;
}

std::map<int,Records> Shop::getProds_Shop() const{
    return prods_shop;
}

void Shop::putProduct(int productID, int amount, int price){
    Records newProduct(productID, amount, price);
    prods_shop[productID] = newProduct;
}

void Shop::printProds_Shop(){
    for(auto it = prods_shop.begin(); it != prods_shop.end(); ++it){
        std::cout << it->first << " " << it->second.getPrice() << " with the amount-> " << it->second.getAmount() << std::endl;
    }
}

void Shop::possibleBuying(int sum){
    for(auto it = prods_shop.begin(); it != prods_shop.end(); ++it){
        int result = 0;
        int i2 = 0;
        while(it->second.getAmount() != 0 && result <= sum){
            result += it->second.getPrice();
//            it->second.decrementAmount();
            if(result <= sum) ++i2;
        }
        if(i2 > 1) std::cout << "You can buy " << i2 << " pieces of a product with ID " << it->second.getRecordsID() << "\n";
        else if (i2 == 1) std::cout << "You can buy " << i2 << " piece of a product with ID " << it->second.getRecordsID() << "\n";
    }
}

int Shop::buy(int productID, int amount){
    int result = 0;
    if(!(prods_shop.find(productID) == prods_shop.end())){
            for(auto it = prods_shop.begin(); it!= prods_shop.end(); ++it){
                if(it->first == productID){
                    if(amount <= it->second.getAmount()){
                        result = it->second.getPrice() * amount;
                        while(amount){
                            it->second.decrementAmount();
                            --amount;
                        }
                    } else throw std::runtime_error("Error! The amount asked for a product is too large within the function Shop::buy().");
                }
            }
        } else throw std::runtime_error("Error! Invalid product ID within the function Shop::buy().");
    return result;
}

bool Shop::isProds_Shop(int prodID){
    bool flag = false;
    for(auto i = prods_shop.begin(); i != prods_shop.end(); ++i) if(i->second.getRecordsID() == prodID) flag = true;
    return flag;
}

int Shop::sumofVector(std::vector<Records> partija){
//    this is only calculating the sum of the products
    int result = 1;
    int Result = 0;
    for(auto i = partija.begin(); i != partija.end(); ++i) if(!isProds_Shop(i->getRecordsID())) throw std::runtime_error("Error! There's no such product in one of the shops within the function Shop::sumofVector().\n");
    
    for(auto it = prods_shop.begin(); it != prods_shop.end(); ++it){
        for(auto it2 = partija.begin(); it2 != partija.end(); ++it2){
            if(it->second.getRecordsID() == it2->getRecordsID()){
                if(it2->getAmount() <= it->second.getAmount()){
                    result = it2->getAmount() * it->second.getPrice();
                    int quant = it2->getAmount();
                    while(quant){
                        it->second.decrementAmount();
                        quant--;
                    }
                    Result += result;
                    result = 1;
                } //else if(it2->getAmount() == 0) throw std::runtime_error("Error! There're no such products in the given shop with the function sumofVector().");
                else {std::cout << it2->getAmount() << " and " << it->second.getAmount() << "\n";throw std::runtime_error("Error! Not enough products in function Shop::sumofVector().");}
            }
        }
    }
    return Result;
}

bool Shop::is_ProdIDinShop(int prodID){
    for(auto it = prods_shop.begin(); it != prods_shop.end(); ++it){
        if(it->first == prodID) return true;
    }
    return false;
}

int Shop::Price(int prodID){
    if (prods_shop.find(prodID) != prods_shop.end()){
        return prods_shop[prodID].getPrice();
    }
        
    else
        return 0;
}

Functional::Functional(){}

Functional::~Functional(){}

void Functional::makeProd(const std::string& prodName){
    Product product(prodName);
    products[product.getProdID()] = product;
}

void Functional::makeShop(const std::string& shopName, const std::string& address){
    Shop shop(shopName, address);
    shops[shop.getShopID()] = shop;
}

void Functional::putProductinShop(Records rec, int shopID){
    for(auto it = shops.begin(); it != shops.end(); ++it){
        if(shopExists(shopID)){
            if(it->second.getShopID() == shopID){
                it->second.putProduct(rec.getRecordsID(), rec.getAmount(), rec.getPrice());
            }
        } else throw std::runtime_error("Error! Invalid shop ID within the function Functional::putProductinShop().");
    }
}

void Functional::putProductsinShop(std::vector<Records> prods, int shopID){
    for(auto it = prods.begin(); it != prods.end(); ++it){
        putProductinShop(*it, shopID);
    }
}

std::pair<int, std::string> Functional::CheapestProduct(int productID){
    int min = INT_MAX;
    std::string Name = "";
    for(auto it = shops.begin(); it != shops.end(); ++it){
        Shop _shop = it->second;
        if(_shop.is_ProdIDinShop(productID)){
            if(min > _shop.Price(productID)){
                min = _shop.Price(productID);
                Name = _shop.getShopName();
            }
        } else throw std::runtime_error("Error! Could not find the product within the function CheapestProduct().");
    }
    return {min, Name};
}

void Functional::ProductsforSum(int shopID, int sum){
    if(!(shops.find(shopID) == shops.end())){
        for(auto it = shops.begin(); it!= shops.end(); ++it){
            if(it->first == shopID){
                std::cout << "For " << sum << "EUR, in " << it->second.getShopName() << "...\n";
                it->second.possibleBuying(sum);
            }
        }
    } else throw std::runtime_error("Error! Invalid shop ID within the function Functional::ProductsforSum().");
}

int Functional::buyingProducts(std::map<int, int> list, int shopID){
    int result = 0;
    if(!(shops.find(shopID) == shops.end())){
        for(auto it = shops.begin(); it!= shops.end(); ++it){
            if(it->first == shopID){
                for(auto it2 = list.begin(); it2 != list.end(); ++it2){
                    result += it->second.buy(it2->first, it2->second);
                }
            }
        }
    } else throw std::runtime_error("Error! Invalid shop ID within the function Functional::buyingProducts().");
    return result;
}

std::pair<int,std::string> Functional::shopProducts(std::vector<Records> partija){
    std::map<int,std::string> result;
    for(auto it = shops.begin(); it != shops.end(); ++it){
        result[it->second.sumofVector(partija)] = it->second.getShopName();
    }
    return {result.begin()->first, result.begin()->second};
}

std::string Functional::getProdName(int prodID) const{
    bool flag = false;
    for(auto it = products.begin(); it != products.end(); ++it){
        if(it->first == prodID){
            flag = true;
            return it->second.getProdName();
        }
    }
    if(!flag) throw std::runtime_error("Error! Could not find the product within the function Functional::getProdName().");
    return "";
}

std::string Functional::getShopName(int shopID) const{
    bool flag = false;
    for(auto it = shops.begin(); it != shops.end(); ++it){
        if(it->first == shopID){
            flag = true;
            return it->second.getShopName();
        }
    }
    if(!flag) throw std::runtime_error("Error! Could not find the shop within the function Functional::getShopName().");
    return "";
}

bool Functional::productExists(int prodID){
    bool flag = false;
    if(products.find(prodID) != products.end()) flag = true;
    
    return flag;
}

bool Functional::productExistsinShop(int shopID, int prodID){
    bool flag = false;
    for(auto it = shops.begin(); it != shops.end(); ++it){
        if(it->second.getShopID() == shopID){
            flag = it->second.isProds_Shop(prodID);
        }
    }
    return flag;
}

bool Functional::shopExists(int shopID){
    bool flag = false;
    for(auto it = shops.begin(); it != shops.end(); ++it){
        if(it->second.getShopID() == shopID) flag = true;
    }
    return flag;
}
