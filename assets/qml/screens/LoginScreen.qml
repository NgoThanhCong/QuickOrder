import QtQuick 2.0
import "../common"
import QtGraphicalEffects 1.0
import QtQml 2.3

Item {
    id : root
    property var pageController: LoginScreenController

    Connections{
        target: LoginScreenModel
        onIsLoginChanged :{
            if(LoginScreenModel.isLogin){
                //Clear Data
                formEmail.textField.text = ""
                formPassword.textField.text = ""
                formEmail.textField.focus = false
                formPassword.textField.focus = false
                app.showMaximized()
            }else{
                app.showNormal();
            }
        }
    }

    Item{
        id : formContainer
        width: ms.LoginScreen.width
        height: parent.height

        TextButton{
            id :btnBack
            anchors{
                left: parent.left
                leftMargin: ms.LoginScreen.margin
                top: parent.top
                topMargin: ms.LoginScreen.topMargin + titleBar.height
            }
            btn_name :"Back to Inspection"
            ic_src: "qrc:/icons/ic_chevron_left.png"
            visible: false
        }

        Item{
            id : form
            height: ms.LoginScreen.form.height
            anchors{
                top: btnBack.bottom
                topMargin: ms.margin.medium_short
                left: parent.left
                right: parent.right
                leftMargin: {ms.LoginScreen.margin + ms.margin.normal}
                rightMargin: {ms.LoginScreen.margin + ms.margin.normal}
            }

            Text{
                id : headerTxt
                anchors{
                    left: parent.left
                    top: parent.top
                    topMargin: ms.margin.normal
                }
                text : "Sign-in"
                color: ms.color.black
                font.bold: true
                height: ms.headerText.lineHeight
                width: parent.width
                font.pixelSize: ms.headerText.fontSize
            }

            FormTextField{
                id : formEmail
                anchors{
                    top: headerTxt.bottom
                    topMargin: {ms.margin.normal*2}
                }
                title: "Username"
                onTextValueChanged: LoginScreenModel.idWarning = ""
                Keys.onTabPressed: formPassword.textField.forceActiveFocus()
            }


            TextNormal{
                id : emailWarning
                color: "#DD1E1E"
                text: LoginScreenModel.idWarning
                height: text !== "" ? lineHeight : 0
                anchors{
                    top: formEmail.bottom
                    topMargin: ms.margin.short
                }
            }

            FormTextField{
                id : formPassword
                anchors{
                    top: emailWarning.bottom
                    topMargin: ms.margin.normal
                }
                title: "Password"
                textField.echoMode: TextInput.Password
                textField.passwordCharacter: "•"
                onTextValueChanged: LoginScreenModel.pwWarning = ""
                Keys.onTabPressed: formPassword.textField.forceActiveFocus()
                Keys.onEnterPressed: btnLogin.btnClicked()
                Keys.onReturnPressed: btnLogin.btnClicked()
            }

            TextNormal{
                id : passwordWarning
                color: "#DD1E1E"
                text: LoginScreenModel.pwWarning
                height: text !== "" ? lineHeight : 0
                anchors{
                    top: formPassword.bottom
                    topMargin: ms.margin.short
                }
            }

            ButtonOutline{
                name: "Login"
                id :btnLogin
                height: ms.LoginScreen.action_button.height
                width: ms.LoginScreen.action_button.width
                anchors{
                    top: passwordWarning.bottom
                    topMargin: ms.margin.normal
                }
                onBtnClicked: pageController.login(formEmail.textValue, formPassword.textValue)
                // onBtnClicked: {
                //     root.visible = false
                //     orderScreen.visible = true
                //     app.showFullScreen()
                // }
            }

            ButtonOutline{
                height: ms.LoginScreen.action_button.height
                width: ms.LoginScreen.action_button.width
                anchors{
                    top: btnLogin.bottom
                    topMargin: ms.margin.normal
                }
                name: "Forgot Password"
                isActive: false
                onBtnClicked: pageController.recoverPassword()
                visible: true
            }
        }
    }

    Rectangle{
        id : informative
        color: ms.color.primary
        height: parent.height
        anchors{
            left: formContainer.right
            right: parent.right
        }
        Image{
            anchors.fill: parent
            source: "qrc:/images/img_layer.png"
        }

        TextNormal{
            text: "Version v1.0"
            height: lineHeight
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: ms.margin.extra_short
            }
            color : "white"
            font.weight: Font.Medium
        }

        Image{
            id : img_logo
            anchors.centerIn: parent
            source: "qrc:/images/logo_vertical.png"
            smooth: true
            fillMode: Image.PreserveAspectFit
        }

        ColorOverlay {
            anchors.fill: img_logo
            source: img_logo
            color: "white"
        }

        Text{
            id : project_name
            anchors{
                left: parent.left
                bottom: img_logo.top
                bottomMargin: ms.margin.extended
            }
            text : "KOI Thé"
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            height: ms.headerText.lineHeight
            width: parent.width
            font.pixelSize: ms.headerText.fontSize
        }
    }
}
