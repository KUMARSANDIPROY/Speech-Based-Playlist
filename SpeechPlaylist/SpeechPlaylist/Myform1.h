#pragma once
#include "Recording.h"
#include"play.h"
#include "obs.h"
#include "HMM.h"
namespace SpeechPlaylist {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Myform1
	/// </summary>
	public ref class Myform1 : public System::Windows::Forms::Form
	{
		public: static Myform1 ^obj1;
	public:
		Myform1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			CheckForIllegalCrossThreadCalls=false;
			obj1=this;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Myform1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::Button^  TAIN;
	private: System::Windows::Forms::Button^  button4;











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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Myform1::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->TAIN = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(291, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(140, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Live Training Module";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(121, 125);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 22);
			this->numericUpDown1->TabIndex = 1;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Myform1::numericUpDown1_ValueChanged_1);
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(349, 128);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(120, 22);
			this->numericUpDown2->TabIndex = 2;
			this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &Myform1::numericUpDown2_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(53, 127);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 17);
			this->label2->TabIndex = 3;
			this->label2->Text = L"word no.";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(247, 130);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(96, 17);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Utterance No.";
			this->label3->Click += gcnew System::EventHandler(this, &Myform1::label3_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(475, 128);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"REC";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Myform1::button3_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(556, 128);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"SAVE";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Myform1::button1_Click_1);
			// 
			// TAIN
			// 
			this->TAIN->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->TAIN->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->TAIN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Indigo;
			this->TAIN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->TAIN->ForeColor = System::Drawing::Color::Black;
			this->TAIN->Location = System::Drawing::Point(65, 302);
			this->TAIN->Name = L"TAIN";
			this->TAIN->Size = System::Drawing::Size(282, 81);
			this->TAIN->TabIndex = 10;
			this->TAIN->Text = L"TRAIN";
			this->TAIN->UseVisualStyleBackColor = true;
			this->TAIN->Click += gcnew System::EventHandler(this, &Myform1::TAIN_Click);
			// 
			// button4
			// 
			this->button4->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button4->FlatAppearance->BorderSize = 50;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(385, 302);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(284, 79);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Update Model";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Myform1::button4_Click);
			// 
			// Myform1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(738, 441);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->TAIN);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->numericUpDown2);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label1);
			this->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Myform1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Myform1";
			this->Load += gcnew System::EventHandler(this, &Myform1::Myform1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			 }
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {

		 }
private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			int i = int::Parse(numericUpDown1->Text);
			int j = int::Parse(numericUpDown2->Text);
			int x=recording1(i,j);
			play();
			
		 }
		
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

			 int i = int::Parse(numericUpDown1->Text);
			int j = int::Parse(numericUpDown2->Text);
			save(i,j);
			
		 }
private: System::Void TAIN_Click(System::Object^  sender, System::EventArgs^  e) {

			 obsgenerate();
			 HMM();

		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 update();
		 }
private: System::Void numericUpDown1_ValueChanged_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Myform1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
