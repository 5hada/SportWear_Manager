
class AlertDialog;


class Dialog{
    AlertDialog* dialog{nullptr};
public:
    Dialog(AlertDialog* dialog): dialog(dialog) {}

    void setDialog(AlertDialog* dialog) {this->dialog = dialog;}

    
};