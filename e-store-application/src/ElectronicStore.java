//Class representing an electronic store
//Has an array of products that represent the items the store can sell
import java.util.List;
import java.util.ArrayList;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import java.util.HashMap;
import java.util.Map;


public class ElectronicStore {
    private String name;
    private List<Product> stock;
    private double revenue;
    private List<Product> cartItems;
    private int salesCount;
    private double currentCartTotal;
    private Map<Product, Integer> products;

    public ElectronicStore(String initName) {
        revenue = 0.0;
        name = initName;
        stock = new ArrayList<>();
        cartItems = new ArrayList<>();
        salesCount = 0;
        currentCartTotal = 0.0;
        this.products = new HashMap<>();
    }

    public String getName() {
        return name;
    }
    public double getRevenue() {
        return revenue;
    }
    public List<Product> getProducts() {return stock;}
    public int getSalesCount(){return salesCount;}
    public double getCurrentCartTotal() {
        return currentCartTotal;
    }

    public Product findProductByName(String name) {
        for (Product product : stock) {
            if (product.getName() != null && product.getName().equalsIgnoreCase(name)) {
                return product;
            }
        }return null;
    }
    public boolean addProduct(Product newProduct) {
        for (int i = 0; i < stock.size(); i++) {
            Product product = stock.get(i);
            if (product.toString().equals(newProduct.toString())) {
                return false;
            }
        }
        stock.add(newProduct);
        return true;
    }

    public void updateTotalAmount() {
        currentCartTotal  = products.entrySet().stream()
                .mapToDouble(e -> e.getKey().getPrice() * e.getValue())
                .sum();
    }

    public ObservableList<String> displayCart() {
        ObservableList<String> items = FXCollections.observableArrayList();
        products.forEach((product, quantity) -> {
            String itemString = quantity + " x " + product;
            items.add(itemString);
        });
        return items;
    }
    public void addToCart(Product product) {
        if (stock.contains(product) && product.getStockQuantity() > 0) {
            cartItems.add(product);
            product.sellUnits(1); //where stock is decremented
            products.put(product, products.getOrDefault(product, 0) + 1); // incrementing the quantity in the map
            updateTotalAmount();
        }
    }

    public void removeFromCart() {
        for (Product product : cartItems) {
            product.returnUnits(products.get(product)); // Return all units of each product to the stock
        }
        cartItems.clear(); // Clear the cart item list
        products.clear(); // Clear the map of products and their quantities
        updateTotalAmount(); // Update the total amount of the cart to reflect the changes
    }

    public void completeSale() {
        revenue += currentCartTotal;
        salesCount++;
        cartItems.clear();
        currentCartTotal = 0.0;
        products.clear();
    }

    public void resetStore() {
        stock.clear();
        cartItems.clear();
        revenue = 0.0;
        salesCount = 0;
        products.clear();
        loadInitialProducts();
    }
    private void loadInitialProducts() {
        ElectronicStore initialStore = createStore();
        this.stock.addAll(initialStore.getProducts());
    }
    public double getRevenuePerSale() {
        if (salesCount > 0) {
            return revenue / salesCount;
        } else {
            return 0.0;
        }
    }
    public ObservableList<Product> getStockItems() {
        ObservableList<Product> items = FXCollections.observableArrayList();
        for (Product product : stock) {
            if (product != null && product.getStockQuantity() > 0) {
                items.add(product);
            }
        }
        return items;
    }
    public ObservableList<Product> getMostPopularItemsX(int count) {
        ObservableList<Product> popularItems = FXCollections.observableArrayList();
        List<Product> sortedStock = new ArrayList<>(stock);
        sortedStock.sort((p1, p2) -> Integer.compare(p2.getSoldQuantity(), p1.getSoldQuantity()));

        // Ensure that we only add the top 'count' popular items, which have been sold at least once
        for (int i = 0; i < Math.min(count, sortedStock.size()); i++) {
            Product product = sortedStock.get(i);
            if (product.getSoldQuantity() > 0) {
                popularItems.add(product);
            }
        }
        return popularItems;
    }


    public static ElectronicStore createStore() {
        ElectronicStore store1 = new ElectronicStore("Watts Up Electronics");
        Desktop d1 = new Desktop(100, 10, 3.0, 16, false, 250, "Compact");
        Desktop d2 = new Desktop(200, 10, 4.0, 32, true, 500, "Server");
        Laptop l1 = new Laptop(150, 10, 2.5, 16, true, 250, 15);
        Laptop l2 = new Laptop(250, 10, 3.5, 24, true, 500, 16);
        Fridge f1 = new Fridge(500, 10, 250, "White", "Sub Zero", false);
        Fridge f2 = new Fridge(750, 10, 125, "Stainless Steel", "Sub Zero", true);
        ToasterOven t1 = new ToasterOven(25, 10, 50, "Black", "Danby", false);
        ToasterOven t2 = new ToasterOven(75, 10, 50, "Silver", "Toasty", true);
        store1.addProduct(d1);
        store1.addProduct(d2);
        store1.addProduct(l1);
        store1.addProduct(l2);
        store1.addProduct(f1);
        store1.addProduct(f2);
        store1.addProduct(t1);
        store1.addProduct(t2);
        return store1;
    }
} 