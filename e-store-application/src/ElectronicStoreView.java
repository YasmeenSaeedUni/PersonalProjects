import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.control.ListView;

public class ElectronicStoreView extends Pane {
    private ListView<Product> storeStock;
    private ListView<String> currentCart;
    private ListView<Product> mostPopularItems;

    private TextField sales;
    private TextField revenue;
    private TextField salesPer;
    private Label label_g;

    private Button resetStore;
    private Button addToCart;
    private Button removeFromCart;
    private Button completeSale;
    private ElectronicStore model;

    public ElectronicStoreView(ElectronicStore model) {
        this.model = model;

        //ListView
        mostPopularItems = new ListView<>();
        mostPopularItems.relocate(10, 160);
        mostPopularItems.setPrefSize(200, 190);

        storeStock = new ListView<>();
        storeStock.relocate(220, 30);
        storeStock.setPrefSize(275, 320);


        currentCart = new ListView<>();
        currentCart.relocate(505, 30);
        currentCart.setPrefSize(275, 320);

        //Textfields
        sales = new TextField();
        sales.relocate(110, 35);
        sales.setPrefSize(100, 20);

        revenue = new TextField();
        revenue.relocate(110, 65);
        revenue.setPrefSize(100, 20);

        salesPer = new TextField();
        salesPer.relocate(110, 95);
        salesPer.setPrefSize(100, 20);


        //Buttons
        Button resetStore = new Button("Reset Store");
        resetStore.setStyle("-fx-font: 12 arial; -fx-text-fill: rgb(0,0,0);");
        resetStore.relocate(45, 360);
        resetStore.setPrefSize(130, 30);

        Button addToCart = new Button("Add to Cart");
        addToCart.setStyle("-fx-font: 12 arial; -fx-base: rgb(255,255,255); -fx-text-fill: rgb(0,0,0);");
        addToCart.relocate(275, 360);
        addToCart.setPrefSize(130, 30);

        Button removeFromCart = new Button("Remove from Cart");
        removeFromCart.setStyle("-fx-font: 12 arial; -fx-base: rgb(255,255,255); -fx-text-fill: rgb(0,0,0);");
        removeFromCart.relocate(509, 360);
        removeFromCart.setPrefSize(130, 30);

        Button completeSale = new Button("Complete Sale");
        completeSale.setStyle("-fx-font: 12 arial; -fx-base: rgb(255,255,255); -fx-text-fill: rgb(0,0,0);");
        completeSale.relocate(639, 360);
        completeSale.setPrefSize(130, 30);

        //Label
        Label label_a = new Label("Store Summary:");
        label_a.relocate(15, 10);

        Label label_b = new Label("# Sales:");
        label_b.relocate(44, 35);

        Label label_c = new Label("Revenue:");
        label_c.relocate(40, 65);

        Label label_d = new Label("$ / Sale:");
        label_d.relocate(44, 95);

        Label label_e = new Label("Most popular Items:");
        label_e.relocate(55, 135);

        Label label_f = new Label("Store Stock:");
        label_f.relocate(320, 10);

        label_g = new Label("Current Cart: ($0.00)");
        label_g.relocate(550, 10);


        this.addToCart = addToCart;
        this.removeFromCart = removeFromCart;
        this.resetStore = resetStore;
        this.completeSale = completeSale;

        this.getChildren().addAll(mostPopularItems, storeStock, currentCart, sales, revenue, salesPer, resetStore, addToCart, removeFromCart, completeSale, label_a, label_b, label_c, label_d, label_e, label_f, label_g);
        update();

    }
    private void update() {}
    public void updateLabelG(double totalAmount) {
        label_g.setText("Current Cart: ($" + String.format("%.2f", totalAmount) + ")");}

    //Getters for ListView
    public ListView <Product> getMostPopularItems(){
        return mostPopularItems;
    }
    public ListView <Product> getStoreStock(){
        return storeStock;
    }
    public ListView <String> getCurrentCart(){
        return currentCart;
    }

    //Getters for TextFields
    public TextField getSales(){
        return sales;
    }
    public TextField getRevenue(){
        return revenue;
    }
    public TextField getSalesPer(){
        return salesPer;
    }

    //Getters for Buttons
    public Button getAddToCart(){
        return addToCart;
    }
    public Button getResetStore(){
        return resetStore;
    }
    public Button getRemoveFromCart(){
        return removeFromCart;
    }
    public Button getCompleteSale(){
        return completeSale;
    }
}
