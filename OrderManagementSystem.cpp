#include <iostream>
#include <string>

using namespace std;

struct Order
{
    static int current_order_id;
    int order_id = ++current_order_id;
    string baked_items;
    int quantity;
    double weight;
    string destination;
    string customer_details;
    string delivery_person_details;
    double profit;
    bool isDelivered = false;
};

int Order::current_order_id = 0;

struct Node
{
    Order data;
    Node *next = nullptr;
};

struct LinkedList
{
    Node *front = nullptr;
    Node *rear = nullptr;

    bool isEmpty()
    {
        return front == nullptr;
    }

    void enqueue(const Order &order)
    {
        Node *newNode = new Node;
        newNode->data = order;
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Order dequeue()
    {
        if (isEmpty())
        {
            cerr << "Queue is empty. Cannot dequeue.\n";
            exit(EXIT_FAILURE);
        }

        Node *temp = front;
        Order order = temp->data;

        if (front == rear)
        {
            front = rear = nullptr;
        }
        else
        {
            front = front->next;
        }

        delete temp;
        return order;
    }
};

void displayCurrentOrders(Node *front)
{
    Node *temp = front;
    while (temp != nullptr)
    {
        string baked_items;
    int quantity;
    double weight;
    string destination;
    string customer_details;
    string delivery_person_details;
    double profit;
    bool isDelivered = false;
        cout << "Order ID: " << temp->data.order_id << "\nItem: " << temp->data.baked_items << "\nQuantity: " << temp->data.quantity << "\nWeight:" << temp->data.weight << endl;
        cout << "\nDestination: " << temp->data.destination << "\nCustomer Name: " << temp->data.customer_details << "\nDelivery Person Name: " << temp->data.delivery_person_details << endl;
        cout << "\nProfit: " << temp->data.profit << "\nDelivery Status: " << temp->data.isDelivered << endl;

        temp = temp->next;
    }
}

void prioritizeOrdersByProfit(Node *front)
{
    Node *current = front;
    while (current != nullptr)
    {
        Node *nextOrder = current->next;
        while (nextOrder != nullptr)
        {
            if (current->data.profit < nextOrder->data.profit)
            {
                swap(current->data, nextOrder->data);
            }
            nextOrder = nextOrder->next;
        }
        current = current->next;
    }

    cout << "Orders prioritized by profit.\n";
}

LinkedList deliveredOrders;

void chooseOrdersForDelivery(Node *&front, const string &delivery_person)
{
    Node *temp = front;
    bool ordersFound = false;
    double max_weight = 40.0;
    double current_weight = 0.0;

    while (temp != nullptr)
    {
        if (temp->data.delivery_person_details == delivery_person)
        {
            if (current_weight + temp->data.weight <= max_weight)
            {
                current_weight += temp->data.weight;
                cout << "Selected Order ID: " << temp->data.order_id << ", Profit: " << temp->data.profit << ", Weight: " << temp->data.weight << " kg" << endl;
                ordersFound = true;

                temp->data.isDelivered = true;

                deliveredOrders.enqueue(temp->data);

                if (temp == front)
                {
                    front = temp->next;
                    delete temp;
                    temp = front;
                }
                else
                {
                    Node *prev = front;
                    while (prev->next != temp)
                    {
                        prev = prev->next;
                    }
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                }
            }
            else
            {
                cout << "Weight limit reached for the delivery person: " << delivery_person << ". Cannot add more orders.\n";
                break;
            }
        }
        else
        {
            temp = temp->next;
        }
    }

    if (!ordersFound)
    {
        cout << "No orders found for " << delivery_person << " within the specified weight limit.\n";
    }
    else
    {
        cout << "Selected orders for delivery by " << delivery_person << ".\n";
    }
}

void showDeliveredOrders()
{
    if (deliveredOrders.isEmpty())
    {
        cout << "No orders have been delivered yet.\n";
        return;
    }

    Node *temp = deliveredOrders.front;
    while (temp != nullptr)
    {
        cout << "Delivered Order ID: " << temp->data.order_id << ", Profit: " << temp->data.profit << ", Weight: " << temp->data.weight << " kg" << endl;
        temp = temp->next;
    }
}

void showAllOrders(Node *orderQueueFront, LinkedList &deliveredOrders)
{
    cout << "\nOrders in Queue:\n";
    displayCurrentOrders(orderQueueFront);

    cout << "\nDelivered Orders:\n";
    if (deliveredOrders.isEmpty())
    {
        cout << "No orders have been delivered yet.\n";
    }
    else
    {
        Node *temp = deliveredOrders.front;
        while (temp != nullptr)
        {
            cout << "Delivered Order ID: " << temp->data.order_id << ", Profit: " << temp->data.profit << ", Weight: " << temp->data.weight << " kg" << endl;
            temp = temp->next;
        }
    }
}

int main()
{
    Node *ordersQueue = nullptr;

    char choice;
    string delivery_person;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add Order\n";
        cout << "2. Display Current Orders\n";
        cout << "3. Prioritize Orders by Profit\n";
        cout << "4. Show All Orders\n";
        cout << "5. Show Delivered Orders\n";
        cout << "6. Choose Orders for Delivery\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            system("cls");
            Order newOrder;

            cout << "Enter Baked Items: ";
            cin.ignore();
            getline(cin, newOrder.baked_items);

            cout << "Enter Quantity: ";
            cin >> newOrder.quantity;

            cout << "Enter Weight (in kg): ";
            cin >> newOrder.weight;

            cout << "Enter Destination: ";
            cin.ignore();
            getline(cin, newOrder.destination);

            cout << "Enter Customer Name: ";
            getline(cin, newOrder.customer_details);

            cout << "Enter Delivery Person Name: ";
            getline(cin, newOrder.delivery_person_details);

            cout << "Enter Profit: ";
            cin >> newOrder.profit;

            Node *newNode = new Node;
            newNode->data = newOrder;
            newNode->next = nullptr;
            if (ordersQueue == nullptr)
            {
                ordersQueue = newNode;
            }
            else
            {
                Node *temp = ordersQueue;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            cout << "Order added successfully.\n";
            break;
        }
        case '2':
            system("cls");
            cout << "\nCurrent Orders:\n";
            displayCurrentOrders(ordersQueue);
            break;
        case '3':
            system("cls");
            prioritizeOrdersByProfit(ordersQueue);
            break;
        case '4':
            system("cls");
            showAllOrders(ordersQueue, deliveredOrders);
            break;
        case '5':
            system("cls");
            showDeliveredOrders();
            break;
        case '6':
            system("cls");
            cout << "\nEnter delivery person's name: ";
            cin.ignore();
            getline(cin, delivery_person);
            chooseOrdersForDelivery(ordersQueue, delivery_person);
            break;
        case '7':
            system("cls");
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    } while (choice != '7');

    return 0;
}