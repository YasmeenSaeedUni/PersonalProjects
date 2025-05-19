//Base class for all products the store will sell
public abstract class Product {
    private double price;
    private int stockQuantity;
    private String name; // Property to store the product's name

    private int soldQuantity;


    public Product(double initPrice, int initQuantity) {
        price = initPrice;
        stockQuantity = initQuantity;
    }

    public String getName() {
        return this.name;
    }
    public int getStockQuantity() {
        return stockQuantity;
    }

    public int getSoldQuantity() {return soldQuantity;}

    public double getPrice() {
        return price;
    }


    public double sellUnits(int amount) {
        if (amount > 0 && stockQuantity >= amount) {
            stockQuantity -= amount;
            soldQuantity += amount;
            return price * amount;
        }
        return 0.0;
    }

    public void returnUnits(int amount) {
        if (amount > 0 && soldQuantity >= amount) {
            stockQuantity += amount;
            soldQuantity -= amount;
        }
    }


}