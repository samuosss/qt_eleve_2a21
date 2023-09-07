#include <iostream>
#include"connexion.h"
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("eleve");
db.setUserName("Malika");//inserer nom de l'utilisateur
db.setPassword("Etoile1925");//inserer mot de passe de cet utilisateur

if (db.open())
{test=true;
}





    return  test;
}
