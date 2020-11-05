//
//  main.cpp
//  shops
//
//  Created by Sara Nikolić on 28.09.2020.
//  Copyright © 2020 Sara Nikolić. All rights reserved.
//

#include <iostream>
#include <vector>
#include "shops.hpp"

int main() {
    
    try{
        
        Functional func1;
        
//        1 - Make a product
        func1.makeProd("banana"); // prodID - 1
        func1.makeProd("ananas"); // prodID - 2
        func1.makeProd("orange"); // prodID - 3
        func1.makeProd("kiwi"); // prodID - 4
        func1.makeProd("apple"); // prodID - 5
        func1.makeProd("lemon"); // prodID - 6
        func1.makeProd("apricot"); // prodID - 7
        func1.makeProd("watermellon"); // prodID - 8
        func1.makeProd("strawberry"); // prodID - 9
        func1.makeProd("raspberry"); // prodID - 10
        
//        2 - Make a shop
        func1.makeShop("Paprika Stores", "6 Ryder's Row"); // shopID - 1
//        3 - Input a group of products into a shop
        Records rec1(1, 100, 23); // productID, amount, price
        Records rec2(4, 50, 21);
        Records rec3(2, 50, 51);
        Records rec4(3, 45, 5);
        Records rec5(5, 30, 21);
        rec2.setPrice(33); // setting/changing the price
        rec5.setPrice(41);
        std::vector<Records> list1 = {rec1, rec2, rec3, rec4, rec5};
        func1.putProductsinShop(list1, 1);
        
        func1.makeShop("Kod Diketa", "Karadjordjeva 5"); // shopID - 2
        Records rec6(1, 50, 15);
        Records rec7(6, 5, 30);
        Records rec8(2, 405, 15);
        Records rec9(4, 15, 20);
        Records rec10(8, 10, 150);
        std::vector<Records> list2 = {rec6, rec7, rec8, rec9, rec10};
        func1.putProductsinShop(list2, 2);
        
        Records rec16(6, 3, 30);
        
        func1.makeShop("Rafael Gomez Salado", "Calle Juan Ajuariaguerra Kalea 40"); // shopID - 3
        Records rec11(10, 4, 5);
        Records rec12(9, 14, 24);
        Records rec13(8, 50, 3);
        Records rec14(1, 49, 2);
        Records rec15(2, 50, 15);
        rec15.setPrice(14);
        std::vector<Records> list3 = {rec11, rec12, rec13, rec14, rec15};
        func1.putProductsinShop(list3, 3);
        
//        4 - Find a shop, in which a certain product is the cheapest
        std::pair<int, std::string> cheapest = func1.CheapestProduct(2);
        std::cout << "- - - CHEAPEST PRODUCT - - -\n";
        std::cout << "A product with the name " << func1.getProdName(2) << " is the cheapest in the shop with the name " << cheapest.second << " and it has a price of " << cheapest.first << "EUR.\n\n";

//        5 - Determine what kinds of products is possible to buy from a certain shop for a specific sum of money
        std::cout << "- - - PRODUCTS FOR SUM - - -\n";
        int money = 250;
        func1.ProductsforSum(3, money);
        std::cout << std::endl;

//        6 - Buy a group of products from a certain shop
        std::cout << "- - - BUYING A LIST OF PRODUCTS - - -\n";
        std::map<int, int> list; // shopping list
        list[1] = 5; // productID, amount
        list[2] = 3;
        list[6] = 2;
        std::cout << "The sum of the products bought is " << func1.buyingProducts(list, 2) << "EUR.\n\n"; // list of things to buy, shopID

//        7 - Find a shop in which the sum of a group of products is the cheapest
        std::cout << "- - - CHEAPEST GROUP OF PRODUCTS - - -\n";
        Records vec1(1, 2, 0); // prodID, amount, null
//        Records vec2(10, 3, 0);
        Records vec3(2, 2, 0);
        std::vector<Records> record;
        record.push_back(vec1);
//        record.push_back(vec2);
        record.push_back(vec3);
        std::pair<int, std::string> result;

        result = func1.shopProducts(record);
        std::cout << "To shop in " << result.second << " is the cheapest possible variant for the given products! :) Total sum will be..." << result.first << "EUR.\n";
        
        std::cout << std::endl << std::endl;
    } catch(std::runtime_error error){
            std::cout << "\nRuntime error occured...\n" <<  error.what() << std::endl;
        }
    
    return 0;
}
