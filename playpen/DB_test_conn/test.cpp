/*
 *  test.cpp
 *  
 *
 *  Created by Benjamin Schmidt on 5/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include <mysql++.h>
#include <iostream>
int main()
{
	const char* db = "nirslab", *server = "10.48.88.131:3306", *user = "theadmin", *pass ="optical";
	
	
	mysqlpp::Connection conn(true);
	std::cout << "Object Created" << std::endl;
	//bool temp = conn.connect(db, server, user, pass);
	//std::cout << temp << std::endl;

	if (conn.connect(db, server, user, pass))
	{
		mysqlpp::Query query = conn.query("select * FROM users");
		if (mysqlpp::StoreQueryResult res = query.store()) {
			std::cout << "We have:" << std::endl;
			for (size_t i = 0; i < res.num_rows(); ++i) {
				std::cout << '\t' << res[i][0] << std::endl;
			}
		}
		
		std::cout<< "here" <<std::endl;
	}
	//std::cout << db << std::endl;
	std::cout << "Program Terminated" <<std::endl;
}
