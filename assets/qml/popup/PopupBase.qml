import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../common"
import ".."

Popup{
    id :  popup_base
    height: 300
    width: 800
    anchors.centerIn: parent
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    margins: 0
    padding: 0
    property string popupTitle: "Settings"
    property alias topBar: titlePopup

    signal discard();

    background: Rectangle{
        anchors.fill: parent
        radius: ms.Windows.radius
        color: ms.color.white
    }

    function isValidDateFormat(dateString) {
        var regex = /^(0[1-9]|[1-2][0-9]|3[0-1])\/(0[1-9]|1[0-2])\/\d{4}$/;
        return regex.test(dateString);
    }

    function isDateGreaterThanOrEqualToToday(dateString) {
        // Parse the date string
        var dateParts = dateString.split("/");
        var inputDate = new Date(dateParts[2], dateParts[1] - 1, dateParts[0]); // Month is 0-indexed

        // Get today's date
        var currentDate = new Date();

        // Set hours, minutes, seconds, and milliseconds to 0 to compare dates without time component
        currentDate.setHours(0, 0, 0, 0);
        inputDate.setHours(0, 0, 0, 0);

        // Compare the input date with today's date
        return inputDate >= currentDate;
    }

    function isValidVietnamesePhoneNumber(phoneNumber) {
        var phoneNumberRegex = /^(03|05|07|08|09)[0-9]{8}$/;
        return phoneNumberRegex.test(phoneNumber);
    }

    function isValidPassword(password) {
        var passw = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{6,20}$/;
        return password.match(passw)
    }

    function resetTextField(input){
        input.textField.color = "black"
        input.textField.font.bold = false
    }

    function wrongFormatField(input){
        input.textField.color = "red"
        input.textField.font.bold = true
    }

    Overlay.modal: Rectangle {
        color: Qt.rgba(0,0,0,0.5)
    }

    Item{
        id : titlePopup
        height: ms.Popup.title_height
        width: parent.width
        TextTitle{
            anchors.left: parent.left
            anchors.leftMargin: ms.margin.normal
            text: popupTitle
            anchors.right: btnClose.left
            font.pixelSize: ms.Popup.title_pixelSize
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            color: ms.color.primary
        }

        ImageButton{
            id : btnClose
            src: "qrc:/icons/ic_close.png"
            height: ms.Popup.title_height
            width: height
            onBtnClicked: {
                popup_base.discard()
                popup_base.close()
            }
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
