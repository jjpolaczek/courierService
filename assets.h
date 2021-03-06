#ifndef ASSETS_H
#define ASSETS_H

#include <random>
#include <vector>
#include "package.h"
#include "vehicle.h"
#include "drawing.h"
#include "customer.h"
#include "point.h"
#include "simtime.h"


class Branch : public DrawableObject, public PackageContainer, public VehicleContainer
{
    friend class Hub;
public:
    Branch(int id, DrawableObject *hub):\
        _hub(hub),
        _id(id),
        _hubSent(false)
    {
        _workStart = 7;
        _workEnd = 16;
        _position.x = rand() % sizex;
        _position.y = rand() % sizey;
    }
    void Draw();
    void Step();
	void Print();

private:
    Customer *FindCustomer(int id);
    void AddCustomers(size_t no)
    {
        for(size_t j =0; j < no; ++j)
        {
            _customers.push_back(new Customer(_position, _id));
        }
        //Also add vehicles according to the customer count//
        int count = _customers.size();
        int vans = count / 15 + 1;
        int trucks =  1;
        int motors = count / 30;
        for(int i = 0; i < vans; ++i)
            _vehicles.push_back(new Van(_position));
        for(int i = 0; i < trucks; ++i)
            _vehicles.push_back(new Truck(_position));
        for(int i = 0; i < motors; ++i)
            _vehicles.push_back(new Scooter(_position));
    }
    DrawableObject *_hub;
    const int _id;
    bool _hubSent;
    std::vector<Customer*> _customers;
};
class Hub : public DrawableObject, public PackageContainer, public VehicleContainer
{
public:
    Hub(int x, int y)
    {
        _workStart = 16;
        _workEnd = 5;
        _position.x = x % sizex;
        _position.y = y % sizey;
    }
    Hub()
    {
        _position.x = rand()%sizex;
        _position.y = rand()%sizey;
    }

    void Draw();
    void Step();
    void GenerateMap(size_t branches, size_t customers_min, size_t customers_max)
    {
        if(_branches.size() > 0)\
            throw std::logic_error("Map already created");
        //Force minimum 1 customer//
        if(customers_max < customers_min)
            throw std::out_of_range("customers_max < customers_min");
        for(size_t i = 0; i < branches; ++i)
        {
            _branches.push_back(new Branch(i,this));
            size_t customers_no = rand()% (customers_max - customers_min)+ customers_min;
            _branches.back()->AddCustomers(customers_no);
        }
    }
	void GetBranchPackages(std::vector<Package*> &packs, int branchid);
	void Print();
private:
    std::vector<Branch*> _branches;
};


#endif // ASSETS_H
