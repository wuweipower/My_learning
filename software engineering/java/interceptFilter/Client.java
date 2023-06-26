package java.interceptFilter;

public class Client {
    FilterManager filterManager;
    public void setFilterManager(FilterManager filterManager)
    {
        this.filterManager = filterManager;
    }

    public void sendRequest(String requst)
    {
        filterManager.filterRequest(requst);
    }
}
