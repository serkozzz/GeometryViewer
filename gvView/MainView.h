#pragma once

#include <map>
#include <string.h>
#include <msclr\marshal_cppstd.h>

#include "../gvViewModel/MainViewModel.h"
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
		/// Summary for MainView
		/// </summary>
		public ref class MainView : public System::Windows::Forms::Form
		{

		private:

			//PointViewModel^ pointVM;
			//BindingList<PointViewModel^>^ pointsVM;


			//MainViewModel^ _mainViewModel;

			MainViewModel^ _viewModel;

			delegate void propChanged(Object^ Sender, PropertyChangedEventArgs^ arg);

		private: System::Windows::Forms::TextBox^  tbTest;
				 System::Windows::Forms::Button^  btnTest;
				 System::Windows::Forms::DataGridView^  dtGrdVPoints;

		public:
			MainView(MainViewModel^ viewModel) : _viewModel(viewModel)
			{
				InitializeComponent();

				dtGrdVPoints->DataSource = _viewModel->PointsVM->GetPoints();

				subscribeToSelectedPoint();

				_viewModel->PropertyChanged += gcnew PropertyChangedEventHandler(this, &MainView::ViewModelPropertyChanged);

				//resetGUI(std::string("point") + std::to_string(_pointsCount));


				//pointVM = gcnew PointViewModel();

				//Binding^ binding = gcnew Binding("Text",
				//	pointVM,
				//	"A",
				//	true,
				//	DataSourceUpdateMode::OnPropertyChanged);

				//tbTest->DataBindings->Add(binding);

				//pointsVM = gcnew BindingList<PointViewModel^>();

				//dtGrdVPoints->DataSource = pointsVM;

				//pointsVM->Add(pointVM);
				//pointsVM->Add(gcnew PointViewModel());
			}

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MainView()
			{
				if (components)
				{
					delete components;
				}
			}


#pragma region methods-helpers
		private:

			void subscribeToSelectedPoint()
			{
				if (_viewModel->SelectedPoint == nullptr)
					return;

				tbX->DataBindings->Add(gcnew Binding("Text",
					_viewModel->SelectedPoint,
					"PositionX",
					true,
					DataSourceUpdateMode::OnPropertyChanged));

				tbY->DataBindings->Add(gcnew Binding("Text",
					_viewModel->SelectedPoint,
					"PositionY",
					true,
					DataSourceUpdateMode::OnPropertyChanged));

				tbZ->DataBindings->Add(gcnew Binding("Text",
					_viewModel->SelectedPoint,
					"PositionZ",
					true,
					DataSourceUpdateMode::OnPropertyChanged));

				tbName->DataBindings->Add(gcnew Binding("Text", 
					_viewModel->SelectedPoint,
					"Name",
					true,
					DataSourceUpdateMode::OnPropertyChanged));
			}



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

			void resetGUI(std::string& nameForNewPoint)
			{
				gv::View::vPoint point(nameForNewPoint, glm::vec3(0, 0, 0), PrimitiveType::cubePrimitiveType);
				setGUIFromIPoint(&point);
			}

			void resetGUI()
			{
				resetGUI(std::string(""));
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


#pragma region ViewModel Events

			void ViewModelPropertyChanged(Object^ Sender, PropertyChangedEventArgs^ arg)
			{
				if (arg->PropertyName == "SelectedPoint")
				{
					subscribeToSelectedPoint();
				}
			}

#pragma endregion ViewModel Events
			



#pragma region GUI Events
		private: System::Void btnAddPoint_Click(System::Object^  sender, System::EventArgs^  e) {
					 _viewModel->viewCreatePointCommand();
				 }

		private: System::Void btnRemovePoint_Click(System::Object^  sender, System::EventArgs^  e) {


				 }


		private: System::Void btnChangePointSize_Click(System::Object^  sender, System::EventArgs^  e) {

				 }


		private: System::Void loadPlanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 //TODO dialog for plan name choosing
				 }


		private: System::Void savePlanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 //TODO dialog for plan name choosing
				 }


#pragma endregion GUI Events


		private: System::Windows::Forms::ListBox^  listboxCameraMatrix;

		private: System::Windows::Forms::Label^  label5;

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
				this->listboxCameraMatrix = (gcnew System::Windows::Forms::ListBox());
				this->label5 = (gcnew System::Windows::Forms::Label());
				this->tbTest = (gcnew System::Windows::Forms::TextBox());
				this->btnTest = (gcnew System::Windows::Forms::Button());
				this->dtGrdVPoints = (gcnew System::Windows::Forms::DataGridView());
				this->panel1->SuspendLayout();
				this->panel2->SuspendLayout();
				this->menuStrip1->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dtGrdVPoints))->BeginInit();
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
				this->panel1->Size = System::Drawing::Size(702, 90);
				this->panel1->TabIndex = 0;
				// 
				// label3
				// 
				this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->label3->AutoSize = true;
				this->label3->Location = System::Drawing::Point(524, 20);
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
				this->cbPrimitiv->Location = System::Drawing::Point(498, 36);
				this->cbPrimitiv->Name = L"cbPrimitiv";
				this->cbPrimitiv->Size = System::Drawing::Size(91, 21);
				this->cbPrimitiv->TabIndex = 9;
				this->cbPrimitiv->Text = L"cube";
				// 
				// panel2
				// 
				this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->panel2->Controls->Add(this->tbZ);
				this->panel2->Controls->Add(this->tbX);
				this->panel2->Controls->Add(this->tbY);
				this->panel2->Controls->Add(this->label2);
				this->panel2->Location = System::Drawing::Point(282, 20);
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
				this->tbName->Size = System::Drawing::Size(264, 20);
				this->tbName->TabIndex = 3;
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
				this->btnRemovePoint->Location = System::Drawing::Point(595, 48);
				this->btnRemovePoint->Name = L"btnRemovePoint";
				this->btnRemovePoint->Size = System::Drawing::Size(93, 39);
				this->btnRemovePoint->TabIndex = 1;
				this->btnRemovePoint->Text = L"remove point";
				this->btnRemovePoint->UseVisualStyleBackColor = true;
				this->btnRemovePoint->Click += gcnew System::EventHandler(this, &MainView::btnRemovePoint_Click);
				// 
				// btnAddPoint
				// 
				this->btnAddPoint->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->btnAddPoint->Location = System::Drawing::Point(595, 3);
				this->btnAddPoint->Name = L"btnAddPoint";
				this->btnAddPoint->Size = System::Drawing::Size(93, 39);
				this->btnAddPoint->TabIndex = 0;
				this->btnAddPoint->Text = L"add new point";
				this->btnAddPoint->UseVisualStyleBackColor = true;
				this->btnAddPoint->Click += gcnew System::EventHandler(this, &MainView::btnAddPoint_Click);
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
				this->menuStrip1->Size = System::Drawing::Size(726, 24);
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
				this->loadPlanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainView::loadPlanToolStripMenuItem_Click);
				// 
				// savePlanToolStripMenuItem
				// 
				this->savePlanToolStripMenuItem->Name = L"savePlanToolStripMenuItem";
				this->savePlanToolStripMenuItem->Size = System::Drawing::Size(126, 22);
				this->savePlanToolStripMenuItem->Text = L"Save Plan";
				this->savePlanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainView::savePlanToolStripMenuItem_Click);
				// 
				// btnChangePointSize
				// 
				this->btnChangePointSize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				this->btnChangePointSize->Location = System::Drawing::Point(335, 121);
				this->btnChangePointSize->Name = L"btnChangePointSize";
				this->btnChangePointSize->Size = System::Drawing::Size(79, 23);
				this->btnChangePointSize->TabIndex = 8;
				this->btnChangePointSize->Text = L"apply";
				this->btnChangePointSize->UseVisualStyleBackColor = true;
				this->btnChangePointSize->Click += gcnew System::EventHandler(this, &MainView::btnChangePointSize_Click);
				// 
				// listboxCameraMatrix
				// 
				this->listboxCameraMatrix->FormattingEnabled = true;
				this->listboxCameraMatrix->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"1, 0, 0, 0", L"0, 1, 0, 0", L"0, 0, 1, 0", 
					L"0, 0, 0, 1"});
				this->listboxCameraMatrix->Location = System::Drawing::Point(433, 148);
				this->listboxCameraMatrix->Name = L"listboxCameraMatrix";
				this->listboxCameraMatrix->Size = System::Drawing::Size(267, 82);
				this->listboxCameraMatrix->TabIndex = 9;
				// 
				// label5
				// 
				this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->label5->AutoSize = true;
				this->label5->Location = System::Drawing::Point(12, 217);
				this->label5->Name = L"label5";
				this->label5->Size = System::Drawing::Size(39, 13);
				this->label5->TabIndex = 11;
				this->label5->Text = L"Points:";

				// dtGrdVPoints
				// 
				this->dtGrdVPoints->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					| System::Windows::Forms::AnchorStyles::Left) 
					| System::Windows::Forms::AnchorStyles::Right));
				this->dtGrdVPoints->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				this->dtGrdVPoints->Location = System::Drawing::Point(0, 234);
				this->dtGrdVPoints->Name = L"dtGrdVPoints";
				this->dtGrdVPoints->Size = System::Drawing::Size(726, 122);
				this->dtGrdVPoints->TabIndex = 14;
				// 
				// MainView
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(726, 354);
				this->Controls->Add(this->dtGrdVPoints);
				this->Controls->Add(this->btnTest);
				this->Controls->Add(this->tbTest);
				this->Controls->Add(this->label5);
				this->Controls->Add(this->listboxCameraMatrix);
				this->Controls->Add(this->btnChangePointSize);
				this->Controls->Add(this->tbPointsSize);
				this->Controls->Add(this->label4);
				this->Controls->Add(this->panel1);
				this->Controls->Add(this->menuStrip1);
				this->MainMenuStrip = this->menuStrip1;
				this->Name = L"MainView";
				this->Text = L"MainView";
				this->panel1->ResumeLayout(false);
				this->panel1->PerformLayout();
				this->panel2->ResumeLayout(false);
				this->panel2->PerformLayout();
				this->menuStrip1->ResumeLayout(false);
				this->menuStrip1->PerformLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dtGrdVPoints))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion


#pragma endregion

		};
	}
}