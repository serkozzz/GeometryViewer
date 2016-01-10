#pragma once

#include <map>
#include <string.h>
#include <msclr\marshal_cppstd.h>

#include "gvView.h"
#include "vPoint.h"

namespace gv
{

	namespace View {

		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Collections;
		using namespace System::Windows::Forms;
		using namespace System::Data;
		using namespace System::Drawing;
		using namespace msclr::interop;
		using namespace System::Runtime::InteropServices;

		/// <summary>
		/// Summary for MainForm
		/// </summary>
		public ref class MainForm : public System::Windows::Forms::Form
		{

		private:



			gvView* _gvView;
			std::map<const skb::EventHandler<const std::shared_ptr<IPoint>& >*, int>* _subscriptions;

			delegate void collectionChanged(std::shared_ptr<IPoint>);
			delegate void propChanged(PointPropChangedArgs args);

			template<typename TDelegateType, typename TArgType>
			void bindHelperMethod(TDelegateType^ del, skb::EventHandler<TArgType>& eventHandler)
			{
				IntPtr funcPointer = Marshal::GetFunctionPointerForDelegate(del);
				eventHandler += static_cast<void (CALLBACK *)(TArgType)>(funcPointer.ToPointer());
			}


		public:
			MainForm(gvView* gvView) : _gvView(gvView)
			{
				_subscriptions = new std::map<const skb::EventHandler<const std::shared_ptr<IPoint>& >*, int>();

				//May be I must save delagates reference as class member
				collectionChanged^ pointAddedEventDel =  gcnew collectionChanged(this, &MainForm::pointAddedEvent);
				bindHelperMethod<collectionChanged, std::shared_ptr<IPoint>>(pointAddedEventDel, _gvView->pointAddedEvent);

				collectionChanged^ pointRemovedEventDel =  gcnew collectionChanged(this, &MainForm::pointRemovedEvent);
				bindHelperMethod<collectionChanged, std::shared_ptr<IPoint>>(pointRemovedEventDel, _gvView->pointRemovedEvent);

				collectionChanged^ pointSelectedEventDel =  gcnew collectionChanged(this, &MainForm::pointSelectedEvent);
				bindHelperMethod<collectionChanged, std::shared_ptr<IPoint>>(pointSelectedEventDel, _gvView->pointSelectedEvent);

				collectionChanged^ pointUnselectedEventDel =  gcnew collectionChanged(this, &MainForm::pointUnselectedEvent);
				bindHelperMethod<collectionChanged, std::shared_ptr<IPoint>>(pointUnselectedEventDel, _gvView->pointUnselectedEvent);

				propChanged^ propChangedDel =  gcnew propChanged(this, &MainForm::selectedPointPropertyChanged);
				bindHelperMethod<propChanged, PointPropChangedArgs>(propChangedDel, _gvView->selectedPointPropChangedEvent);

				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//
			}


		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MainForm()
			{
				if (components)
				{
					delete _subscriptions;
					delete components;
				}
			}
		private: System::Windows::Forms::Panel^  panel1;
		private: System::Windows::Forms::Button^  btnAddPoint;
		private: System::Windows::Forms::Button^  btnRemovePoint;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::ComboBox^  cbPrimitiv;

		private: System::Windows::Forms::Panel^  panel2;
		private: System::Windows::Forms::TextBox^  tbZ;

		private: System::Windows::Forms::TextBox^  tbX;
		private: System::Windows::Forms::TextBox^  tbY;


		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::TextBox^  tbName;

		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::TextBox^  tbPointsSize;
		private: System::Windows::Forms::MenuStrip^  menuStrip1;
		private: System::Windows::Forms::ToolStripMenuItem^  menuToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  loadPlanToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  savePlanToolStripMenuItem;
		private: System::Windows::Forms::Button^  btnChangePointSize;
		protected: 


		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->panel1 = (gcnew System::Windows::Forms::Panel());
				this->label3 = (gcnew System::Windows::Forms::Label());
				this->cbPrimitiv = (gcnew System::Windows::Forms::ComboBox());
				this->panel2 = (gcnew System::Windows::Forms::Panel());
				this->tbZ = (gcnew System::Windows::Forms::TextBox());
				this->tbX = (gcnew System::Windows::Forms::TextBox());
				this->tbY = (gcnew System::Windows::Forms::TextBox());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->tbName = (gcnew System::Windows::Forms::TextBox());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->btnRemovePoint = (gcnew System::Windows::Forms::Button());
				this->btnAddPoint = (gcnew System::Windows::Forms::Button());
				this->label4 = (gcnew System::Windows::Forms::Label());
				this->tbPointsSize = (gcnew System::Windows::Forms::TextBox());
				this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->loadPlanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->savePlanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->btnChangePointSize = (gcnew System::Windows::Forms::Button());
				this->panel1->SuspendLayout();
				this->panel2->SuspendLayout();
				this->menuStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// panel1
				// 
				this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->panel1->Controls->Add(this->label3);
				this->panel1->Controls->Add(this->cbPrimitiv);
				this->panel1->Controls->Add(this->panel2);
				this->panel1->Controls->Add(this->tbName);
				this->panel1->Controls->Add(this->label1);
				this->panel1->Controls->Add(this->btnRemovePoint);
				this->panel1->Controls->Add(this->btnAddPoint);
				this->panel1->Location = System::Drawing::Point(12, 23);
				this->panel1->Name = L"panel1";
				this->panel1->Size = System::Drawing::Size(554, 90);
				this->panel1->TabIndex = 0;
				// 
				// label3
				// 
				this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->label3->AutoSize = true;
				this->label3->Location = System::Drawing::Point(376, 20);
				this->label3->Name = L"label3";
				this->label3->Size = System::Drawing::Size(27, 13);
				this->label3->TabIndex = 10;
				this->label3->Text = L"form";
				// 
				// cbPrimitiv
				// 
				this->cbPrimitiv->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->cbPrimitiv->FormattingEnabled = true;
				this->cbPrimitiv->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"cube", L"sphere"});
				this->cbPrimitiv->Location = System::Drawing::Point(350, 36);
				this->cbPrimitiv->Name = L"cbPrimitiv";
				this->cbPrimitiv->Size = System::Drawing::Size(91, 21);
				this->cbPrimitiv->TabIndex = 9;
				this->cbPrimitiv->Text = L"cube";
				this->cbPrimitiv->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::cbPrimitiv_SelectedValueChanged);
				// 
				// panel2
				// 
				this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->panel2->Controls->Add(this->tbZ);
				this->panel2->Controls->Add(this->tbX);
				this->panel2->Controls->Add(this->tbY);
				this->panel2->Controls->Add(this->label2);
				this->panel2->Location = System::Drawing::Point(134, 20);
				this->panel2->Name = L"panel2";
				this->panel2->Size = System::Drawing::Size(210, 48);
				this->panel2->TabIndex = 8;
				// 
				// tbZ
				// 
				this->tbZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->tbZ->Location = System::Drawing::Point(139, 16);
				this->tbZ->Name = L"tbZ";
				this->tbZ->Size = System::Drawing::Size(61, 20);
				this->tbZ->TabIndex = 7;
				this->tbZ->Text = L"0";
				this->tbZ->Leave += gcnew System::EventHandler(this, &MainForm::tbZ_Leave);
				// 
				// tbX
				// 
				this->tbX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Left));
				this->tbX->Location = System::Drawing::Point(5, 16);
				this->tbX->Name = L"tbX";
				this->tbX->Size = System::Drawing::Size(61, 20);
				this->tbX->TabIndex = 5;
				this->tbX->Text = L"0";
				this->tbX->Leave += gcnew System::EventHandler(this, &MainForm::tbX_Leave);
				// 
				// tbY
				// 
				this->tbY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->tbY->Location = System::Drawing::Point(72, 16);
				this->tbY->Name = L"tbY";
				this->tbY->Size = System::Drawing::Size(61, 20);
				this->tbY->TabIndex = 6;
				this->tbY->Text = L"0";
				this->tbY->Leave += gcnew System::EventHandler(this, &MainForm::tbY_Leave);
				// 
				// label2
				// 
				this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->label2->AutoSize = true;
				this->label2->Location = System::Drawing::Point(79, 0);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(43, 13);
				this->label2->TabIndex = 4;
				this->label2->Text = L"position";
				// 
				// tbName
				// 
				this->tbName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->tbName->Location = System::Drawing::Point(12, 36);
				this->tbName->Name = L"tbName";
				this->tbName->Size = System::Drawing::Size(116, 20);
				this->tbName->TabIndex = 3;
				this->tbName->Leave += gcnew System::EventHandler(this, &MainForm::tbName_Leave);
				// 
				// label1
				// 
				this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->label1->AutoSize = true;
				this->label1->Location = System::Drawing::Point(54, 20);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(33, 13);
				this->label1->TabIndex = 2;
				this->label1->Text = L"name";
				// 
				// btnRemovePoint
				// 
				this->btnRemovePoint->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
				this->btnRemovePoint->Location = System::Drawing::Point(447, 48);
				this->btnRemovePoint->Name = L"btnRemovePoint";
				this->btnRemovePoint->Size = System::Drawing::Size(93, 39);
				this->btnRemovePoint->TabIndex = 1;
				this->btnRemovePoint->Text = L"remove point";
				this->btnRemovePoint->UseVisualStyleBackColor = true;
				this->btnRemovePoint->Click += gcnew System::EventHandler(this, &MainForm::btnRemovePoint_Click);
				// 
				// btnAddPoint
				// 
				this->btnAddPoint->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->btnAddPoint->Location = System::Drawing::Point(447, 3);
				this->btnAddPoint->Name = L"btnAddPoint";
				this->btnAddPoint->Size = System::Drawing::Size(93, 39);
				this->btnAddPoint->TabIndex = 0;
				this->btnAddPoint->Text = L"add new point";
				this->btnAddPoint->UseVisualStyleBackColor = true;
				this->btnAddPoint->Click += gcnew System::EventHandler(this, &MainForm::btnAddPoint_Click);
				// 
				// label4
				// 
				this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->label4->AutoSize = true;
				this->label4->Location = System::Drawing::Point(66, 126);
				this->label4->Name = L"label4";
				this->label4->Size = System::Drawing::Size(57, 13);
				this->label4->TabIndex = 3;
				this->label4->Text = L"Points size";
				// 
				// tbPointsSize
				// 
				this->tbPointsSize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Left));
				this->tbPointsSize->Location = System::Drawing::Point(129, 123);
				this->tbPointsSize->Name = L"tbPointsSize";
				this->tbPointsSize->Size = System::Drawing::Size(44, 20);
				this->tbPointsSize->TabIndex = 6;
				this->tbPointsSize->Text = L"10";
				// 
				// menuStrip1
				// 
				this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->menuToolStripMenuItem});
				this->menuStrip1->Location = System::Drawing::Point(0, 0);
				this->menuStrip1->Name = L"menuStrip1";
				this->menuStrip1->Size = System::Drawing::Size(578, 24);
				this->menuStrip1->TabIndex = 7;
				this->menuStrip1->Text = L"menuStrip1";
				// 
				// menuToolStripMenuItem
				// 
				this->menuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->loadPlanToolStripMenuItem, 
					this->savePlanToolStripMenuItem});
				this->menuToolStripMenuItem->Name = L"menuToolStripMenuItem";
				this->menuToolStripMenuItem->Size = System::Drawing::Size(50, 20);
				this->menuToolStripMenuItem->Text = L"Menu";
				// 
				// loadPlanToolStripMenuItem
				// 
				this->loadPlanToolStripMenuItem->Name = L"loadPlanToolStripMenuItem";
				this->loadPlanToolStripMenuItem->Size = System::Drawing::Size(126, 22);
				this->loadPlanToolStripMenuItem->Text = L"Load Plan";
				this->loadPlanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadPlanToolStripMenuItem_Click);
				// 
				// savePlanToolStripMenuItem
				// 
				this->savePlanToolStripMenuItem->Name = L"savePlanToolStripMenuItem";
				this->savePlanToolStripMenuItem->Size = System::Drawing::Size(126, 22);
				this->savePlanToolStripMenuItem->Text = L"Save Plan";
				this->savePlanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::savePlanToolStripMenuItem_Click);
				// 
				// btnChangePointSize
				// 
				this->btnChangePointSize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->btnChangePointSize->Location = System::Drawing::Point(187, 121);
				this->btnChangePointSize->Name = L"btnChangePointSize";
				this->btnChangePointSize->Size = System::Drawing::Size(79, 23);
				this->btnChangePointSize->TabIndex = 8;
				this->btnChangePointSize->Text = L"apply";
				this->btnChangePointSize->UseVisualStyleBackColor = true;
				this->btnChangePointSize->Click += gcnew System::EventHandler(this, &MainForm::btnChangePointSize_Click);
				// 
				// MainForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(578, 171);
				this->Controls->Add(this->btnChangePointSize);
				this->Controls->Add(this->tbPointsSize);
				this->Controls->Add(this->label4);
				this->Controls->Add(this->panel1);
				this->Controls->Add(this->menuStrip1);
				this->MainMenuStrip = this->menuStrip1;
				this->Name = L"MainForm";
				this->Text = L"MainForm";
				this->panel1->ResumeLayout(false);
				this->panel1->PerformLayout();
				this->panel2->ResumeLayout(false);
				this->panel2->PerformLayout();
				this->menuStrip1->ResumeLayout(false);
				this->menuStrip1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion


#pragma region methods-helpers
		private:
			vPoint getvPointFromGUI()
			{
				std::string name = marshal_as< std::string >(tbName->Text);

				std::string xStr =  marshal_as< std::string >(tbX->Text);
				std::string yStr =  marshal_as< std::string >(tbY->Text);
				std::string zStr =  marshal_as< std::string >(tbZ->Text);

				glm::vec3 pos(std::stof(xStr), std::stof(yStr), std::stof(zStr));

				PrimitiveType primitive = getPrimitiveTypeFromStr(cbPrimitiv->Text);
				return vPoint(name, pos, primitive);
			}

			void setGUIFromIPoint(const IPoint* point)
			{
				tbName->Text = gcnew String(point->getName().c_str());
				tbX->Text = System::Convert::ToString(point->getPosition().x);
				tbY->Text = System::Convert::ToString(point->getPosition().y);
				tbZ->Text = System::Convert::ToString(point->getPosition().z);

				cbPrimitiv->Text = getStrFromPrimitiveType(point->getPrimitive());
			}

			void resetGUI()
			{
				gv::View::vPoint point("", glm::vec3(0, 0, 0), PrimitiveType::cubePrimitiveType);
				setGUIFromIPoint(&point);
			}

			System::String^ getStrFromPrimitiveType(PrimitiveType primitive)
			{
				if (primitive == PrimitiveType::cubePrimitiveType)
					return "cube";
				else if(primitive == PrimitiveType::spherePrimitiveType)
					return "sphere";

				throw std::invalid_argument("Unknown Primitive Type: " + std::to_string(primitive));
			}


			PrimitiveType getPrimitiveTypeFromStr(String^ str)
			{
				if (str == "cube")
					return PrimitiveType::cubePrimitiveType;
				else if(str = "sphere")
					return PrimitiveType::spherePrimitiveType;

				throw std::invalid_argument("Unknown Primitive Type: " + marshal_as< std::string >(str));
			}
#pragma endregion methods-helpers

#pragma region GUI Events
		private: System::Void btnAddPoint_Click(System::Object^  sender, System::EventArgs^  e) {

					 if (_gvView->addPointClick != nullptr)
					 {
						 _gvView->addPointClick(std::make_shared<vPoint>(getvPointFromGUI()));
					 }
				 }

		private: System::Void btnRemovePoint_Click(System::Object^  sender, System::EventArgs^  e) {

					 if (_gvView->addPointClick != nullptr)
					 {
						 _gvView->removePointClick(_gvView->getSelectedPoint());
					 }
				 }


		private: System::Void btnChangePointSize_Click(System::Object^  sender, System::EventArgs^  e) {

					 if (_gvView->changePointSizeClick != nullptr)
					 {
						 std::string pointSizeStr = marshal_as< std::string >(tbY->Text);
						 int pointSize = std::stoi(pointSizeStr);
						 _gvView->changePointSizeClick(pointSize);
					 }
				 }


		private: System::Void loadPlanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 if (_gvView->loadPlanClick != nullptr)
					 {
						 //TODO dialog for plan name choosing
						 _gvView->loadPlanClick("test plan name");
					 }
				 }
		private: System::Void savePlanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 if (_gvView->savePlanClick != nullptr)
					 {
						 //TODO dialog for plan name choosing
						 _gvView->savePlanClick("test plan name");
					 }

				 }

		private: System::Void tbX_Leave(System::Object^  sender, System::EventArgs^  e) {
					 _gvView->getSelectedPoint()->trySetPosition(getvPointFromGUI().getPosition());
				 }

		private: System::Void tbY_Leave(System::Object^  sender, System::EventArgs^  e) {
					 _gvView->getSelectedPoint()->trySetPosition(getvPointFromGUI().getPosition());
				 }

		private: System::Void tbZ_Leave(System::Object^  sender, System::EventArgs^  e) {
					 _gvView->getSelectedPoint()->trySetPosition(getvPointFromGUI().getPosition());
				 }

		private: System::Void tbName_Leave(System::Object^  sender, System::EventArgs^  e) {
					 _gvView->getSelectedPoint()->trySetName(getvPointFromGUI().getName());
				 }

		private: System::Void cbPrimitiv_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
					 _gvView->getSelectedPoint()->trySetPrimitive(getvPointFromGUI().getPrimitive());
				 }

#pragma endregion GUI Events

#pragma region Model Events

				 void pointAddedEvent(std::shared_ptr<IPoint> p)
				 {
					 int a = 10;
					 a++;
				 }

				 void pointRemovedEvent(std::shared_ptr<IPoint> p)
				 {
				 }

				 void pointSelectedEvent(/*args is not used*/ std::shared_ptr<IPoint> p)
				 {
					 setGUIFromIPoint(_gvView->getSelectedPoint().get());
				 }

				 void pointUnselectedEvent(/*args is not used*/ std::shared_ptr<IPoint> p)
				 {
					 resetGUI();
				 }

				 void selectedPointPropertyChanged(PointPropChangedArgs arg)
				 {
					 setGUIFromIPoint(_gvView->getSelectedPoint().get());
				 }


#pragma endregion Model Events

		};

#pragma endregion
	}
}