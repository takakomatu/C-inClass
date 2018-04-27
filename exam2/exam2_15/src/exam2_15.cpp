class Publisher
{
    char pub[12];
    double turnover;
  protected:
    void Register();
  public:
    Publisher();
    void enter();
    void display();
};
class Branch
{
    char city[20];
  protected:
    float employees;
  public:
    Branch();
    void haveit();
    void giveit();
};
class Author : private Branch, public Publisher
{
    int acode;
    char aname[20];
    float amount;
  public:
    Author();
    void start();
    void show()
    {
    	// pub[0] = 'a';
    	// turnover = 0;
    	employees = 1.2;
    }
};

int main(){
	Author a;
	a.show();
}
