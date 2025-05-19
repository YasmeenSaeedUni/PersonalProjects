import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;

public class ElectronicStoreApp extends Application {

    private ElectronicStore model;
    private ElectronicStoreView view;

    public ElectronicStoreApp() {
        model = ElectronicStore.createStore(); // This should initialize the store with items.
        view = new ElectronicStoreView(model);
    }

    public void start(Stage primaryStage) {
        Pane aPane = new Pane();
        view = new ElectronicStoreView(model);
        aPane.getChildren().add(view);

        // Add window title
        primaryStage.setTitle("Electronic Store Application - " + model.getName());


        // Populate ListViews
        view.getStoreStock().setItems(FXCollections.observableArrayList(model.getStockItems()));

        // Disable the buttons
        if (view.getAddToCart() != null) {
            view.getAddToCart().setDisable(true);
        }
        if (view.getRemoveFromCart() != null) {
            view.getRemoveFromCart().setDisable(true);
        }
        if (view.getCompleteSale() != null) {
            view.getCompleteSale().setDisable(true);
        }

        view.getSales().setText("0");
        view.getRevenue().setText("0.00");
        view.getSalesPer().setText("N/A");


        //Store Stock
        view.getStoreStock().setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                boolean isSelected = view.getStoreStock().getSelectionModel().getSelectedItem() != null;
                view.getAddToCart().setDisable(!isSelected);
            }
        });

        //Add to Cart
        view.getAddToCart().setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                Product selectedItem = view.getStoreStock().getSelectionModel().getSelectedItem();
                if (selectedItem != null && selectedItem.getStockQuantity() > 0) {
                    model.addToCart(selectedItem);
                    updateStoreStock(); // Refresh the stock list view
                    updateCurrentCart();
                    view.getCompleteSale().setDisable(false);
                }
            }
        });

        //Current cart
        view.getCurrentCart().setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                boolean isSelected = view.getCurrentCart().getSelectionModel().getSelectedItem() != null;
                view.getRemoveFromCart().setDisable(!isSelected);
            }
        });

        // Remove  from Cart
        view.getRemoveFromCart().setOnAction(event -> {
            model.removeFromCart();
            updateCurrentCart();
            updateStoreStock(); 
        });


        //Complete Sale
        view.getCompleteSale().setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                model.completeSale();
                view.getSales().setText(String.valueOf(model.getSalesCount()));
                view.getRevenue().setText(String.format("%.2f", model.getRevenue()));
                view.getSalesPer().setText(String.format("%.2f", model.getRevenuePerSale()));
                updateCurrentCart();
                updatePopularItems();
                view.getCompleteSale().setDisable(true);
            }
        });

        //Reset Store
        view.getResetStore().setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                model.resetStore();
                updateStoreStock();
                updateCurrentCart();
                updatePopularItems();
                view.getSales().setText("0");
                view.getRevenue().setText("0.00");
                view.getSalesPer().setText("N/A");
            }
        });

        // Set the scene and show the stage
        primaryStage.setScene(new Scene(aPane, 800, 400));
        primaryStage.show();
    }
    private void updateStoreStock() {
        view.getStoreStock().setItems(FXCollections.observableArrayList(model.getStockItems())); // Refresh the stock list
        view.getStoreStock().refresh(); // Ensure the ListView is updated visually
    }

    private void updateCurrentCart() {
        view.getCurrentCart().setItems(model.displayCart());
        view.getCurrentCart().refresh();
        view.updateLabelG(model.getCurrentCartTotal());
    }

    private void updatePopularItems() {
        view.getMostPopularItems().setItems(FXCollections.observableArrayList(model.getMostPopularItemsX(3)));
        view.getMostPopularItems().refresh();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

