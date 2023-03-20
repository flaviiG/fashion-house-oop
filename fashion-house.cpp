#include <iostream>
#include <exception>
#include <stdexcept>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <typeinfo>
#include <stdlib.h>

using namespace std;

class IOinterface
{
public:
    virtual istream& Citire(istream&)=0;
    virtual ostream& Afisare(ostream&)const=0;
};

class Articol: public IOinterface
{
protected:
    string nume;
    string tip_articol;
    int stoc;
    float pret;

public:
    void reducere(Articol& a)
    {
        if(a.stoc<10)
            a.pret-=a.pret/10;
    }
    Articol()
    {
        nume="Unkown";
        tip_articol="Unknown";
        stoc=0;
        pret=0;
    }
    Articol(string nume, string tip_articol, int stoc, float pret)
    {
        this->nume=nume;
        this->tip_articol=tip_articol;
        this->stoc=stoc;
        this->pret=pret;
        reducere(*this);
    }
    Articol(const Articol& a)
    {
        this->nume=a.nume;
        this->tip_articol=a.tip_articol;
        this->stoc=a.stoc;
        this->pret=a.pret;
    }
    Articol operator= (const Articol& a)
    {
        if(this!=&a)
        {
            this->nume=a.nume;
            this->tip_articol=a.tip_articol;
            this->stoc=a.stoc;
            this->pret=a.pret;
        }
        return *this;
    }

    virtual istream& Citire(istream& in)
    {
        cout<<"Numele: ";
        in>>this->nume;
        cout<<"Tipul: ";
        in>>this->tip_articol;
        cout<<"Cate bucati sunt in stoc: ";
        in>>this->stoc;
        cout<<"Pretul: ";
        in>>this->pret;
        if(this->stoc<10)
            this->pret-=this->pret/10;
        return in;
    }
    virtual ostream& Afisare(ostream& out)const
    {
        out<<"Numele: "<<this->nume<<endl;
        out<<"Tipul: "<<this->tip_articol<<endl;
        out<<"Cate bucati sunt in stoc: "<<this->stoc<<endl;
        out<<"Pretul: "<<this->pret<<endl;
        return out;
    }
    friend istream& operator>> (istream& in, Articol& c)
    {
        return c.Citire(in);
    }
    friend ostream& operator<< (ostream& out, const Articol& c)
    {
        return c.Afisare(out);
    }
    Articol operator-- ()
    {
        if(this->stoc>0)
            this->stoc-=1;
        if(this->stoc<10)
            this->pret-=(this->pret)/10;
        return *this;
    }
    float getPret()const
    {
        return pret;
    }
    string getNume()
    {
        return nume;
    }
    bool getStoc()
    {
        if(stoc>0)
            return true;
        return false;
    }
    bool operator<(const Articol& a) const
    {
        return pret<a.pret;
    }
    ~Articol() {}
};

class Sacou: public virtual Articol
{
protected:
    string marime_sacou;
public:
    Sacou():Articol()
    {
        marime_sacou="Unknown";
    }
    Sacou(string nume, string tip_articol, int stoc, float pret, string marime_sacou):Articol(nume, tip_articol, stoc, pret)
    {
        this->marime_sacou=marime_sacou;
    }
    Sacou(const Sacou& s):Articol(s)
    {
        this->marime_sacou=s.marime_sacou;
    }
    Sacou operator= (const Sacou& s)
    {
        if(this!=&s)
        {
            Articol::operator=(s);
            this->marime_sacou=s.marime_sacou;
        }
        return *this;

    }
    virtual istream& Citire(istream& in)
    {
        Articol::Citire(in);
        return in;
    }
    virtual ostream& Afisare(ostream& out)const
    {
        Articol::Afisare(out);
        out<<"Marime sacou: "<<this->marime_sacou;
        return out;
    }
    friend istream& operator>> (istream& in, Sacou &s)
    {
        in>>(Articol&)s;
        cout<<"Marime sacou: ";
        in>>s.marime_sacou;
        return in;
    }
    friend ostream& operator<< (ostream& out, const Sacou& s)
    {
        out<<(Articol&)s;
        out<<"Marime sacou: "<<s.marime_sacou;
        return out;
    }
    float getPret()const
    {
        return pret;
    }
    string getNume()
    {
        return nume;
    }
    ~Sacou() {}

};

class Pantaloni: public virtual Articol
{
protected:
    string marime_pantaloni;
public:
    Pantaloni():Articol()
    {
        marime_pantaloni="Unknown";
    }
    Pantaloni(string nume, string tip_articol, int stoc, float pret, string marime_pantaloni):Articol(nume, tip_articol, stoc, pret)
    {
        this->marime_pantaloni=marime_pantaloni;
    }
    Pantaloni(const Pantaloni& s):Articol(s)
    {
        this->marime_pantaloni=s.marime_pantaloni;
    }
    Pantaloni operator= (const Pantaloni& s)
    {
        if(this!=&s)
        {
            Articol::operator=(s);
            this->marime_pantaloni=s.marime_pantaloni;
        }
        return *this;

    }
    virtual istream& Citire(istream& in)
    {
        Articol::Citire(in);
        return in;
    }
    virtual ostream& Afisare(ostream& out)const
    {
        Articol::Afisare(out);
        out<<"Marime pantaloni: "<<this->marime_pantaloni;
        return out;
    }
    friend istream& operator>> (istream& in, Pantaloni &s)
    {
        in>>(Articol&)s;
        cout<<"Marime pantaloni: ";
        in>>s.marime_pantaloni;
        return in;
    }
    friend ostream& operator<< (ostream& out, const Pantaloni& s)
    {
        out<<(Articol&)s;
        out<<"Marime pantaloni: "<<s.marime_pantaloni;
        return out;
    }
    float getPret()const
    {
        return pret;
    }
    string getNume()
    {
        return nume;
    }
    ~Pantaloni() {}
};

class Costum:public virtual Sacou,
    public virtual Pantaloni
{
protected:
    string stil;
public:
    Costum():Sacou(),Pantaloni(),Articol()
    {
        stil="Unknown";
    }
    Costum(string nume, string tip_articol, int stoc, float pret, string marime_sacou, string marime_pantaloni, string stil):Sacou(nume, tip_articol, stoc, pret, marime_sacou),Pantaloni(nume, tip_articol, stoc, pret, marime_pantaloni),Articol(nume, tip_articol, stoc, pret)
    {
        this->stil=stil;
    }
    Costum(const Costum& c):Sacou(c),Pantaloni(c),Articol(c)
    {
        this->stil=c.stil;
    }
    Costum operator= (const Costum& c)
    {
        if(this!=&c)
        {
            Sacou::operator=(c);
            this->marime_pantaloni=c.marime_pantaloni;
            this->stil=c.stil;
        }
        return *this;
    }
    virtual istream& Citire(istream& in)
    {
        Sacou::Citire(in);
        return in;
    }
    virtual ostream& Afisare(ostream& out)const
    {
        Sacou::Afisare(out);
        out<<endl;
        out<<"Marime pantaloni: "<<this->marime_pantaloni<<endl;
        out<<"Stil: "<<this->stil<<endl;
        return out;
    }
    friend istream& operator>>(istream& in, Costum& c)
    {
        in>>(Sacou&)c;
        cout<<"Marime pantaloni: ";
        in>>c.marime_pantaloni;
        cout<<"Stil: ";
        in>>c.stil;
        return in;
    }
    friend ostream& operator<<(ostream& out, Costum& c)
    {
        out<<(Sacou&)c<<endl;
        out<<"Marime pantaloni: "<<c.marime_pantaloni<<endl;
        out<<"Stil: "<<c.stil<<endl;
        return out;
    }
    float getPret()const
    {
        return pret;
    }
    string getNume()
    {
        return nume;
    }
    ~Costum() {}
};

template < int lungime=5,class T=int>
class Cos
{
    T* v;
    int n;

public:
    Cos()
    {
        v=new T[lungime];
        n=0;
    }
    Cos (T v[], int n)
    {

        this->v=new T[lungime];
        this->n=n;

        for(int i=0; i<lungime; i++)
            this->v[i]=v[i];


    }
    void afisare()const
    {
        if(n==0)
            cout<<"Cosul este gol"<<endl;
        else
        {
            for(int i=1; i<=n; i++)
                {
                    cout<<*v[i]<<endl;
                }
        }

    }

    T operator[](unsigned int x)
    {
        return v[x];
    }

    void adaugare(const T &a)
    {
        n++;
        v[n]=a;
    }

    int getNr()
    {
        return n;
    }

    void setNr(int x)
    {
        n=x;
    }

    void empty()
    {
        n=0;
        if(v)
        {
            free(v);
            v=NULL;
            v=new T[lungime];
        }
    }
    ~Cos(){
        if(v)
        {
            free(v);
            v=NULL;
        }
    }

};


class Customer: public IOinterface
{
private:
    string nume;
    string prenume;
    string nrtel;
    string status;
    Cos <100,Articol*> cos;
public:
    Customer()
    {
        nume="Unknown";
        prenume="Unknown";
        nrtel="Unknown";
        status="Unknown";
    }
    Customer(string nume, string prenume, string nrtel, string status)
    {
        this->nume=nume;
        this->prenume=prenume;
        this->nrtel=nrtel;
        this->status=status;
    }
    Customer(const Customer& c)
    {
        this->nume=c.nume;
        this->prenume=c.prenume;
        this->nrtel=c.nrtel;
        this->status=c.status;
    }
    Customer operator= (const Customer& c)
    {
        if(this!=&c)
        {
            this->nume=c.nume;
            this->prenume=c.prenume;
            this->nrtel=c.nrtel;
            this->status=c.status;
        }
        return *this;
    }
    virtual istream& Citire(istream& in)
    {
        cout<<"Numele: ";
        in>>this->nume;
        cout<<"Prenumele: ";
        in>>this->prenume;
        cout<<"Numarul de telefon: ";
        in>>this->nrtel;
        cout<<"Status client: ";
        in>>this->status;
        return in;
    }
    virtual ostream& Afisare(ostream& out)const
    {
        out<<"Numele: "<<this->nume<<endl;
        out<<"Prenumele: "<<this->prenume<<endl;
        out<<"Numarul de telefon: "<<this->nrtel<<endl;
        out<<"Status client: "<<this->status<<endl<<endl;
        out<<"Cos cuparaturi: "<<endl;
        this->cos.afisare();

        return out;
    }
    friend istream& operator>> (istream& in, Customer& c)
    {
        return c.Citire(in);
    }
    friend ostream& operator<< (ostream& out, const Customer& c)
    {
        return c.Afisare(out);
    }

    Customer operator+= (Articol& a)
    {
        cos.adaugare(&a);
        return *this;
    }

    void Checkout()
    {
        int s=0;
        int n=cos.getNr();
        if(n==0)
            throw runtime_error("Cosul este gol");
        for(int i=1; i<=n; i++)
            s+=(cos[i])->getPret();

        if(status=="VIP")
            s-=s/10;

        for(int i=1; i<=n; i++)
            --(*cos[i]);


        cout<<"TOTAL: "<<s<<endl;
    }

    void stergeArticol(Articol &a)
    {
        for(int i=1;i<=cos.getNr();i++)
            if((cos[i])->getNume() == a.getNume())
            {
                for(int j=i;j<cos.getNr();j++)
                    *cos[j]=(*cos[j+1]);
                cos.setNr(cos.getNr()-1);
            }
    }

    string getNumePrenume()
    {
        string aux;
        aux=nume+" "+prenume;
        return aux;
    }
    ~Customer() {}
};


int main()
{

    set<Articol*> lista_articole;
    map<int, Customer> lista_customeri;
//    list<Comanda> lista_comenzi;

    map<int, Customer>::iterator itc;
    set<Articol*>::iterator ita;

//   Articol* lista_articole[101];
//   Customer* lista_customeri[101];
//   int na=0,nc=0,k,p,j;
    int k,p,j,nc=0,i;
    do
    {
        cout<<"1 - ADD Articol"<<endl;
        cout<<"2 - ADD Customer"<<endl;
        cout<<"3 - ADAUGA PRODUS IN COS"<<endl;
        cout<<"4 - CHECKOUT"<<endl;
        cout<<"5 - AFISARE ARTICOLE"<<endl;
        cout<<"6 - AFISARE CUSTOMERI"<<endl;
        cout<<"7 - DELETE CUSTOMER"<<endl;
        cout<<"8 - DELETE ARTICOL"<<endl;
        cout<<"0 - EXIT"<<endl;
        cin>>k;
        switch(k)
        {
        case 1:
        {
            cout<<"Alege ce articol vrei sa adaugi:"<<endl;
            cout<<"1 - Sacou"<<endl;
            cout<<"2 - Pantaloni"<<endl;
            cout<<"3 - Costum"<<endl;
            cout<<"4 - ALTCEVA"<<endl;
            cin>>p;
            switch(p)
            {
            case 1:
            {
                Sacou *a;
                a=new Sacou();
                cin>>*a;
                lista_articole.insert(a);
                break;
            }
            case 2:
            {
                Pantaloni *a;
                a=new Pantaloni();
                cin>>*a;
                lista_articole.insert(a);
                break;
            }
            case 3:
            {
                Costum *a;
                a=new Costum();
                cin>>*a;
                lista_articole.insert(a);
                break;
            }
            case 4:
            {
                Articol *a;
                a=new Articol();
                cin>>*a;
                lista_articole.insert(a);
                break;
            }
            }
            break;
        }
        case 2:
        {
            nc++;
            Customer c;
            cin>>c;
            lista_customeri.insert(pair<int,Customer>(nc,c));
            break;
        }
        case 3:
        {
            cout<<"Alege numarul customerului:"<<endl;
            for(itc=lista_customeri.begin(); itc!=lista_customeri.end(); itc++)
                cout<<itc->first<<". "<<itc->second.getNumePrenume()<<endl;
            cin>>p;

            int i=0;
            cout<<"Alege numarul produsului:"<<endl;
            for(ita=lista_articole.begin(); ita!=lista_articole.end(); ita++)
            {
                i++;
                cout<<i<<". "<<(**ita).getNume()<<endl;

            }
            cin>>j;
            ita=lista_articole.begin();
            advance(ita,j-1);

            lista_customeri.find(p)->second+=**ita;
            break;
            }
        case 4:
        {
            cout<<"Alege numarul customerului:"<<endl;
            for(itc=lista_customeri.begin(); itc!=lista_customeri.end(); itc++)
                cout<<itc->first<<". "<<itc->second.getNumePrenume()<<endl;
            cin>>p;
            try
            {
                lista_customeri.find(p)->second.Checkout();
            }
            catch(exception &e)
            {
                cout<<e.what()<<endl;
            }

            break;
        }
        case 5:
        {
            if(lista_articole.empty())
                cout<<"Nu exista produse in magazin!"<<endl;
            else
                for(ita=lista_articole.begin(); ita!=lista_articole.end(); ita++)
                {
                    cout<<**ita<<endl;
                }
            break;
        }
        case 6:
        {
            for(itc=lista_customeri.begin(); itc!=lista_customeri.end(); itc++)
                cout<<itc->second<<endl;

            break;
            }
        case 7:
            {
            cout<<"Alege numarul customerului:"<<endl;
            for(itc=lista_customeri.begin(); itc!=lista_customeri.end(); itc++)
                cout<<itc->first<<". "<<itc->second.getNumePrenume()<<endl;

            try
            {
                cin>>p;
                if(p>nc)
                throw runtime_error("Numarul cusomerului gresit");
            }
            catch(exception &e)
            {
                cout<<e.what()<<endl;
            }
            for(int i=p;i<=nc;i++)
                lista_customeri[i]=lista_customeri[i+1];
            nc--;

            break;
            }
        case 8:
            {
            cout<<"Alege numarul produsului:"<<endl;
            i=1;
            for(ita=lista_articole.begin();ita!=lista_articole.end();ita++)
            {
                cout<<i<<". "<<(**ita).getNume()<<endl;
                i++;
            }
            cin>>j;
            ita=lista_articole.begin();
            advance(ita,j-1);
            Articol* aux = (*ita);
            lista_articole.erase(ita);

            for(itc = lista_customeri.begin();itc!=lista_customeri.end();itc++)
                itc->second.stergeArticol(*aux);
            }

        }

    }
    while(k!=0);

    return 0;
}
