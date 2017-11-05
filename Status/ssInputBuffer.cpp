#include <ssInputBuffer.h>
#include <thread>

// constructor (primeste argumente doar in faza de debug a aplicatiei)
ssInputBuffer::ssInputBuffer(const char*a, int b) : execution(Execution::Ready)
{
    set(a,b);
}

// execute - va fi apelata cand utilizatorul a hotarat sa trimita comanda scrisa in editor spre executie
// detaliu de implementare : tine pe loc thread-ul gui pana thread-ul business trimite comanda spre inter-
// pretator si primeste output-ul
void ssInputBuffer::execute(void)
{
    executionMutex.lock();
    execution = Execution::Ready;
    executionMutex.unlock();

    while(execution != Execution::Done)
    {
        std::chrono::milliseconds timeToSleep(2);
        std::this_thread::sleep_for(timeToSleep);
    }
}

// executionDone - va fi apelata de catre layer-ul bussines si are rolul de a scoate thread-ul gui din
// asteptare (presupunand ca a fost pus in asteptare prin metoda execute() )
void ssInputBuffer::executionDone (void)
{
    executionMutex.lock();
    execution = Execution::Done;
    executionMutex.unlock();
}

// set - metoda va fi apelata numai din layer-ul gui si va seta buffer-ul de input
void ssInputBuffer::set(const char *begining, int size)
{
    this->clean();
    
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    for(int i = 0; i < size; i++)
    {
        data.push_back(begining[i]);
    }

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

}

// clean - goleste buffer-ul de input - a fost conceputa pentru cazul in care utilizatorul apasa sageata-sus
// respectiv sageata-jos, iar buffer-ul va trebui curatat
void ssInputBuffer::clean(void)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.clear();

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

}

// push - metoda care pune cate un caracter la sfarsitul buffer-ului de input - e presupusa a fi mai eficienta
// decat metoda set, mai ales cand utilizatorul tasteaza caracter cu caracter
void ssInputBuffer::push(char ch)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.push_back(ch);

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

}

// pop - metoda inversa metodei push, a se citi documentatia push
void ssInputBuffer::pop(void)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.pop_back();

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

}

// read - metoda vizibila public, va fi folosita din layer-ul de bussines pentru a se vedea ce string
// a tastat utilizatorul
std::string ssInputBuffer::read()
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    std::string dataS(data.begin(), data.end());
    
    stateMutex.lock();
    state = Unmodified;
    stateMutex.unlock();
    
    return dataS;
}