#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Method.h"
#include "Task.h"
const double PI = 3.1415;

double f1(double x,double v1,double v2,double g, double L) {
	return v2;
}

double f2(double x, double v1, double v2, double g, double L) {
	return -g*v1/L;
}

std::vector<double> method_RK_4_count(double L, double g, double x, double v1, double v2, double h) { //(7) в методичке
	double k1[2], k2[2], k3[2],k4[2];
	std::vector<double> result;
	k1[0] = f1(x,v1,v2,g,L);
	k1[1] = f2(x, v1, v2, g, L);
	k2[0] = f1(x+h/2, v1+h*k1[0]/2, v2+ h * k1[1] / 2, g, L);
	k2[1] = f2(x + h / 2, v1 + h * k1[0] / 2, v2 + h * k1[1] / 2, g, L);
	k3[0] = f1(x + h / 2, v1 + h * k2[0] / 2, v2 + h * k2[1] / 2, g, L);
	k3[1] = f2(x + h / 2, v1 + h * k2[0] / 2, v2 + h * k2[1] / 2, g, L);
	k4[0] = f1(x + h, v1 + h * k3[0], v2 + h * k3[1], g, L);
	k4[1] = f2(x + h, v1 + h * k3[0], v2 + h * k3[1], g, L);
	result.push_back(x + h);//x[n+1]
	result.push_back(v1 + h * (k1[0] + 2 * k2[0]+2*k3[0]+k4[0])/6);//v1[n+1]
	result.push_back(v2 + h * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) / 6);//v2[n+1]
	return result;
}

void method_RK_4(double L, double g, int& n, std::vector<double>& x, std::vector<double>& v1, std::vector<double>& v2, double& h) {
	std::vector<double> result;
	result = method_RK_4_count(L, g, x[n], v1[n], v2[n], h);
	x.push_back(result[0]);
	v1.push_back(result[1]);
	v2.push_back(result[2]);
	n++;
}

std::vector<double> method_RK_4_with_control_lp(double L, double g, int& n, std::vector<double>& x, std::vector<double>& v1, std::vector<double>& v2, double& h, double eps) {
	std::vector<double> characteristics_for_table(4); //[S*,Vудв,V'удв,S]
	std::vector<double> result1,result2;//[xn,Vn,V'n]
	double x_12 = x[n], v1_12 = v1[n], v2_12 = v2[n];
	result1 = method_RK_4_count(L, g,x[n], v1[n], v2[n], h); //решение методом РК с шагом h
	result2 = method_RK_4_count(L, g,x_12, v1_12, v2_12, h/2);
	result2 = method_RK_4_count(L, g,result2[0], result2[1], result2[2], h / 2); //решение с половинными шагом
	double S, S1, S2;
	S1 = (result2[1] - result1[1]) / 15;
	S2 = (result2[2] - result1[2]) / 15;
	S = std::max(abs(S1),abs(S2));
	if ((abs(S) >= eps / 32) && (abs(S) <= eps)) {
		x.push_back(result1[0]);
		v1.push_back(result1[1]);
		v2.push_back(result1[2]);
		n++;
	}
	if  (abs(S) < eps/32) {
		/*x.push_back(result2[0]);
		v1.push_back(result2[1]);
		v2.push_back(result2[2]);*/
		x.push_back(result1[0]);
		v1.push_back(result1[1]);
		v2.push_back(result1[2]);
		h *= 2;
		n++;
	}
	if (abs(S) > eps) {
		h = h / 2;
		return method_RK_4_with_control_lp(L, g,n, x, v1, v2, h, eps);
	}
	characteristics_for_table[0] = S * 16;
	characteristics_for_table[1] = result2[1];
	characteristics_for_table[2] = result2[2];
	characteristics_for_table[3] = S;
	return characteristics_for_table;
}


namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Task11_Mironova
	/// </summary>
	public ref class Task11_Mironova : public System::Windows::Forms::Form
	{
	public:
		Task11_Mironova(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Task11_Mironova()
		{
			if (components)
			{
				delete components;
			}
		}





	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::DataGridView^ dataGridView1;









	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;


	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox8;











	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label9;


	private: System::Windows::Forms::TextBox^ textBox10;


	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBox22;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::TextBox^ textBox21;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::TextBox^ textBox20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::TextBox^ textBox18;
	private: System::Windows::Forms::TextBox^ textBox19;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label19;











	private: System::Windows::Forms::TextBox^ textBox32;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::TextBox^ textBox31;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::TextBox^ textBox30;

	private: System::Windows::Forms::TextBox^ textBox29;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::TextBox^ textBox28;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::TextBox^ textBox27;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::TextBox^ textBox26;
	private: System::Windows::Forms::TextBox^ textBox25;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::TextBox^ textBox24;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::TextBox^ textBox23;
	private: System::Windows::Forms::Label^ label24;
private: System::Windows::Forms::Label^ label34;
private: System::Windows::Forms::TextBox^ textBox33;


private: System::Windows::Forms::TextBox^ textBox36;
private: System::Windows::Forms::TextBox^ textBox35;
private: System::Windows::Forms::Label^ label37;
private: System::Windows::Forms::Label^ label36;
private: System::Windows::Forms::Label^ label38;
private: System::Windows::Forms::TextBox^ textBox37;
private: System::Windows::Forms::Label^ label39;
private: System::Windows::Forms::TextBox^ textBox38;
private: System::Windows::Forms::Label^ label40;
private: System::Windows::Forms::TextBox^ textBox39;
















private: System::Windows::Forms::TextBox^ textBox42;
private: System::Windows::Forms::Label^ label43;
private: System::Windows::Forms::TextBox^ textBox41;
private: System::Windows::Forms::Label^ label42;
















private: System::Windows::Forms::GroupBox^ groupBox2;
private: System::Windows::Forms::GroupBox^ groupBox3;
private: System::Windows::Forms::GroupBox^ groupBox4;
private: System::Windows::Forms::Label^ label45;
private: System::Windows::Forms::TextBox^ textBox44;
private: System::Windows::Forms::Label^ label46;
private: System::Windows::Forms::Button^ button1;
private: System::Windows::Forms::Button^ button4;
private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart3;
private: System::Windows::Forms::TextBox^ textBox11;
private: System::Windows::Forms::Label^ label10;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ n;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ hi;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ xn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Vn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Col5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ S;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Un;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
private: System::ComponentModel::IContainer^ components;














	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->n = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->hi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->xn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Vn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Col5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->S = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Un = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox30 = (gcnew System::Windows::Forms::TextBox());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->textBox42 = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->textBox41 = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->textBox36 = (gcnew System::Windows::Forms::TextBox());
			this->textBox35 = (gcnew System::Windows::Forms::TextBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->textBox33 = (gcnew System::Windows::Forms::TextBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox32 = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox31 = (gcnew System::Windows::Forms::TextBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->textBox29 = (gcnew System::Windows::Forms::TextBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textBox28 = (gcnew System::Windows::Forms::TextBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->textBox27 = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->textBox26 = (gcnew System::Windows::Forms::TextBox());
			this->textBox25 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->textBox37 = (gcnew System::Windows::Forms::TextBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->textBox38 = (gcnew System::Windows::Forms::TextBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->textBox39 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox44 = (gcnew System::Windows::Forms::TextBox());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->ItemColumnSpacing = 10;
			legend1->MaximumAutoSize = 30;
			legend1->Name = L"Legend1";
			legend1->TitleAlignment = System::Drawing::StringAlignment::Near;
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(-24, 261);
			this->chart1->Name = L"chart1";
			series1->BorderWidth = 2;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Legend = L"Legend1";
			series1->MarkerBorderColor = System::Drawing::Color::White;
			series1->MarkerColor = System::Drawing::Color::White;
			series1->Name = L"Численное решение";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->Legend = L"Legend1";
			series2->Name = L"Series2";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(671, 307);
			this->chart1->TabIndex = 5;
			this->chart1->Text = L"chart1";
			title1->Alignment = System::Drawing::ContentAlignment::TopCenter;
			title1->BackColor = System::Drawing::Color::White;
			title1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			title1->Name = L"Зависимость угла отклонения маятника от вертикали от времени u(x)";
			title1->Text = L"Зависимость угла отклонения маятника от вертикали от времени u(x)";
			this->chart1->Titles->Add(title1);
			this->chart1->Click += gcnew System::EventHandler(this, &Task11_Mironova::chart1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->button2->FlatAppearance->BorderColor = System::Drawing::SystemColors::HotTrack;
			this->button2->FlatAppearance->BorderSize = 2;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button2->Location = System::Drawing::Point(84, 229);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(132, 33);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Запуск";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Task11_Mironova::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button3->Location = System::Drawing::Point(244, 229);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(106, 31);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Очистить";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Task11_Mironova::button3_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(14) {
				this->n, this->hi,
					this->xn, this->Vn, this->Column1, this->Col5, this->Column2, this->S, this->Un, this->Column3, this->Column4, this->Column5,
					this->Column8, this->Column9
			});
			this->dataGridView1->Location = System::Drawing::Point(653, 280);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(692, 288);
			this->dataGridView1->TabIndex = 8;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Task11_Mironova::dataGridView1_CellContentClick_1);
			// 
			// n
			// 
			this->n->HeaderText = L"n";
			this->n->Name = L"n";
			// 
			// hi
			// 
			this->hi->HeaderText = L"hn";
			this->hi->Name = L"hi";
			// 
			// xn
			// 
			this->xn->HeaderText = L"xn";
			this->xn->Name = L"xn";
			// 
			// Vn
			// 
			this->Vn->HeaderText = L"Vn";
			this->Vn->Name = L"Vn";
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"V\'n";
			this->Column1->Name = L"Column1";
			// 
			// Col5
			// 
			this->Col5->HeaderText = L"Vn_удв";
			this->Col5->Name = L"Col5";
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"V\'n_удв.";
			this->Column2->Name = L"Column2";
			// 
			// S
			// 
			this->S->HeaderText = L"S*";
			this->S->Name = L"S";
			// 
			// Un
			// 
			this->Un->HeaderText = L"Un";
			this->Un->Name = L"Un";
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"U\'n";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"|Un-Vn итог|";
			this->Column4->Name = L"Column4";
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"|U\'n-V\'n итог|";
			this->Column5->Name = L"Column5";
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Ум.шага";
			this->Column8->Name = L"Column8";
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Ув.шага";
			this->Column9->Name = L"Column9";
			// 
			// chart2
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->Enabled = false;
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(653, 594);
			this->chart2->Name = L"chart2";
			series3->BorderWidth = 2;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series3->Legend = L"Legend1";
			series3->MarkerBorderWidth = 2;
			series3->Name = L"Series1";
			series3->YValuesPerPoint = 2;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series4->Legend = L"Legend1";
			series4->Name = L"Series2";
			this->chart2->Series->Add(series3);
			this->chart2->Series->Add(series4);
			this->chart2->Size = System::Drawing::Size(692, 330);
			this->chart2->TabIndex = 9;
			this->chart2->Text = L"chart2";
			title2->Alignment = System::Drawing::ContentAlignment::TopCenter;
			title2->BackColor = System::Drawing::Color::White;
			title2->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			title2->IsDockedInsideChartArea = false;
			title2->Name = L"Фазовый портрет";
			title2->Text = L"Зависимость угловой скорости маятника от угла его отклонения u\'(u)";
			this->chart2->Titles->Add(title2);
			this->chart2->Click += gcnew System::EventHandler(this, &Task11_Mironova::chart2_Click);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(261, 23);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(159, 22);
			this->textBox3->TabIndex = 12;
			this->textBox3->Text = L"0,001";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox3_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(6, 26);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(108, 16);
			this->label2->TabIndex = 13;
			this->label2->Text = L"Начальный шаг";
			this->label2->Click += gcnew System::EventHandler(this, &Task11_Mironova::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(6, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(186, 16);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Параметр контроля лп, eps";
			this->label3->Click += gcnew System::EventHandler(this, &Task11_Mironova::label3_Click);
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->Location = System::Drawing::Point(261, 47);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(159, 22);
			this->textBox4->TabIndex = 15;
			this->textBox4->Text = L"1E-13";
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox4_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(7, 27);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 16);
			this->label4->TabIndex = 16;
			this->label4->Text = L"L";
			this->label4->Click += gcnew System::EventHandler(this, &Task11_Mironova::label4_Click);
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox5->Location = System::Drawing::Point(28, 24);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(137, 22);
			this->textBox5->TabIndex = 17;
			this->textBox5->Text = L"0,1";
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox5_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(6, 29);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(21, 16);
			this->label5->TabIndex = 18;
			this->label5->Text = L"x0";
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox6->Location = System::Drawing::Point(37, 23);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(128, 22);
			this->textBox6->TabIndex = 19;
			this->textBox6->Text = L"0";
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox6_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(6, 53);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(22, 16);
			this->label6->TabIndex = 20;
			this->label6->Text = L"u0";
			// 
			// textBox7
			// 
			this->textBox7->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox7->Location = System::Drawing::Point(37, 47);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(128, 22);
			this->textBox7->TabIndex = 21;
			this->textBox7->Text = L"0,31415";
			this->textBox7->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox7_TextChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(6, 75);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(25, 16);
			this->label7->TabIndex = 22;
			this->label7->Text = L"u\'0";
			// 
			// textBox8
			// 
			this->textBox8->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox8->Location = System::Drawing::Point(37, 72);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(128, 22);
			this->textBox8->TabIndex = 23;
			this->textBox8->Text = L"0";
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox8_TextChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(6, 99);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(166, 16);
			this->label8->TabIndex = 25;
			this->label8->Text = L"Правая граница оси x , b";
			// 
			// textBox9
			// 
			this->textBox9->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox9->Location = System::Drawing::Point(261, 96);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(159, 22);
			this->textBox9->TabIndex = 27;
			this->textBox9->Text = L"0,64";
			this->textBox9->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox9_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->groupBox1->Controls->Add(this->textBox11);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->textBox30);
			this->groupBox1->Controls->Add(this->label45);
			this->groupBox1->Controls->Add(this->textBox42);
			this->groupBox1->Controls->Add(this->label43);
			this->groupBox1->Controls->Add(this->textBox41);
			this->groupBox1->Controls->Add(this->label42);
			this->groupBox1->Controls->Add(this->textBox36);
			this->groupBox1->Controls->Add(this->textBox35);
			this->groupBox1->Controls->Add(this->label37);
			this->groupBox1->Controls->Add(this->label36);
			this->groupBox1->Controls->Add(this->textBox33);
			this->groupBox1->Controls->Add(this->label34);
			this->groupBox1->Controls->Add(this->textBox32);
			this->groupBox1->Controls->Add(this->label33);
			this->groupBox1->Controls->Add(this->textBox31);
			this->groupBox1->Controls->Add(this->label32);
			this->groupBox1->Controls->Add(this->textBox29);
			this->groupBox1->Controls->Add(this->label30);
			this->groupBox1->Controls->Add(this->textBox28);
			this->groupBox1->Controls->Add(this->label29);
			this->groupBox1->Controls->Add(this->textBox27);
			this->groupBox1->Controls->Add(this->label28);
			this->groupBox1->Controls->Add(this->textBox26);
			this->groupBox1->Controls->Add(this->textBox25);
			this->groupBox1->Controls->Add(this->label27);
			this->groupBox1->Controls->Add(this->label26);
			this->groupBox1->Controls->Add(this->textBox24);
			this->groupBox1->Controls->Add(this->label25);
			this->groupBox1->Controls->Add(this->textBox23);
			this->groupBox1->Controls->Add(this->label24);
			this->groupBox1->Controls->Add(this->textBox22);
			this->groupBox1->Controls->Add(this->label23);
			this->groupBox1->Controls->Add(this->textBox21);
			this->groupBox1->Controls->Add(this->label22);
			this->groupBox1->Controls->Add(this->textBox20);
			this->groupBox1->Controls->Add(this->label21);
			this->groupBox1->Controls->Add(this->textBox18);
			this->groupBox1->Controls->Add(this->textBox19);
			this->groupBox1->Controls->Add(this->label20);
			this->groupBox1->Controls->Add(this->label19);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->textBox10);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(653, 2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(698, 260);
			this->groupBox1->TabIndex = 29;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Справка";
			// 
			// textBox11
			// 
			this->textBox11->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox11->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox11->Location = System::Drawing::Point(250, 44);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(87, 15);
			this->textBox11->TabIndex = 68;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(19, 44);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(234, 16);
			this->label10->TabIndex = 67;
			this->label10->Text = L"Контроль локальной погрешности:";
			// 
			// textBox30
			// 
			this->textBox30->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox30->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox30->Location = System::Drawing::Point(285, 186);
			this->textBox30->Name = L"textBox30";
			this->textBox30->Size = System::Drawing::Size(128, 15);
			this->textBox30->TabIndex = 45;
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label45->Location = System::Drawing::Point(235, 185);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(55, 16);
			this->label45->TabIndex = 66;
			this->label45->Text = L"при xn=";
			// 
			// textBox42
			// 
			this->textBox42->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox42->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox42->Location = System::Drawing::Point(555, 228);
			this->textBox42->Name = L"textBox42";
			this->textBox42->Size = System::Drawing::Size(131, 15);
			this->textBox42->TabIndex = 63;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label43->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label43->Location = System::Drawing::Point(503, 227);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(55, 16);
			this->label43->TabIndex = 62;
			this->label43->Text = L"при xn=";
			// 
			// textBox41
			// 
			this->textBox41->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox41->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox41->Location = System::Drawing::Point(355, 228);
			this->textBox41->Name = L"textBox41";
			this->textBox41->Size = System::Drawing::Size(146, 15);
			this->textBox41->TabIndex = 61;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label42->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label42->Location = System::Drawing::Point(18, 227);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(341, 16);
			this->label42->TabIndex = 60;
			this->label42->Text = L"Оценка глобальной погрешности max|U\'n-V\'n итог|=";
			// 
			// textBox36
			// 
			this->textBox36->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox36->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox36->Location = System::Drawing::Point(555, 206);
			this->textBox36->Name = L"textBox36";
			this->textBox36->Size = System::Drawing::Size(137, 15);
			this->textBox36->TabIndex = 57;
			this->textBox36->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox36_TextChanged);
			// 
			// textBox35
			// 
			this->textBox35->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox35->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox35->Location = System::Drawing::Point(346, 207);
			this->textBox35->Name = L"textBox35";
			this->textBox35->Size = System::Drawing::Size(155, 15);
			this->textBox35->TabIndex = 56;
			this->textBox35->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox35_TextChanged);
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label37->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label37->Location = System::Drawing::Point(503, 206);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(55, 16);
			this->label37->TabIndex = 55;
			this->label37->Text = L"при xn=";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label36->Location = System::Drawing::Point(18, 207);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(335, 16);
			this->label36->TabIndex = 54;
			this->label36->Text = L"Оценка глобальной погрешности max|Un-Vn итог|=";
			// 
			// textBox33
			// 
			this->textBox33->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox33->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox33->Location = System::Drawing::Point(506, 87);
			this->textBox33->Name = L"textBox33";
			this->textBox33->Size = System::Drawing::Size(145, 15);
			this->textBox33->TabIndex = 51;
			this->textBox33->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox33_TextChanged);
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label34->Location = System::Drawing::Point(440, 87);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(71, 16);
			this->label34->TabIndex = 50;
			this->label34->Text = L"v\'N_итог=";
			// 
			// textBox32
			// 
			this->textBox32->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox32->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox32->Location = System::Drawing::Point(506, 183);
			this->textBox32->Name = L"textBox32";
			this->textBox32->Size = System::Drawing::Size(58, 15);
			this->textBox32->TabIndex = 49;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label33->Location = System::Drawing::Point(444, 183);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(67, 16);
			this->label33->TabIndex = 48;
			this->label33->Text = L"Ум.шага=";
			// 
			// textBox31
			// 
			this->textBox31->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox31->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox31->Location = System::Drawing::Point(506, 162);
			this->textBox31->Name = L"textBox31";
			this->textBox31->Size = System::Drawing::Size(67, 15);
			this->textBox31->TabIndex = 47;
			this->textBox31->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox31_TextChanged);
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(445, 162);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(66, 16);
			this->label32->TabIndex = 46;
			this->label32->Text = L"Ув.шага=";
			this->label32->Click += gcnew System::EventHandler(this, &Task11_Mironova::label32_Click);
			// 
			// textBox29
			// 
			this->textBox29->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox29->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox29->Location = System::Drawing::Point(69, 185);
			this->textBox29->Name = L"textBox29";
			this->textBox29->Size = System::Drawing::Size(150, 15);
			this->textBox29->TabIndex = 43;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(18, 185);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(53, 16);
			this->label30->TabIndex = 42;
			this->label30->Text = L"min hn=";
			// 
			// textBox28
			// 
			this->textBox28->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox28->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox28->Location = System::Drawing::Point(285, 165);
			this->textBox28->Name = L"textBox28";
			this->textBox28->Size = System::Drawing::Size(128, 15);
			this->textBox28->TabIndex = 41;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label29->Location = System::Drawing::Point(235, 164);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(55, 16);
			this->label29->TabIndex = 40;
			this->label29->Text = L"при xn=";
			// 
			// textBox27
			// 
			this->textBox27->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox27->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox27->Location = System::Drawing::Point(73, 166);
			this->textBox27->Name = L"textBox27";
			this->textBox27->Size = System::Drawing::Size(146, 15);
			this->textBox27->TabIndex = 39;
			this->textBox27->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox27_TextChanged);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label28->Location = System::Drawing::Point(18, 165);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(57, 16);
			this->label28->TabIndex = 38;
			this->label28->Text = L"max hn=";
			// 
			// textBox26
			// 
			this->textBox26->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox26->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox26->Location = System::Drawing::Point(285, 145);
			this->textBox26->Name = L"textBox26";
			this->textBox26->Size = System::Drawing::Size(128, 15);
			this->textBox26->TabIndex = 37;
			// 
			// textBox25
			// 
			this->textBox25->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox25->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox25->Location = System::Drawing::Point(285, 126);
			this->textBox25->Name = L"textBox25";
			this->textBox25->Size = System::Drawing::Size(128, 15);
			this->textBox25->TabIndex = 36;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(235, 145);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(55, 16);
			this->label27->TabIndex = 35;
			this->label27->Text = L"при xn=";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label26->Location = System::Drawing::Point(235, 126);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(55, 16);
			this->label26->TabIndex = 34;
			this->label26->Text = L"при xn=";
			// 
			// textBox24
			// 
			this->textBox24->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox24->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox24->Location = System::Drawing::Point(66, 145);
			this->textBox24->Name = L"textBox24";
			this->textBox24->Size = System::Drawing::Size(159, 15);
			this->textBox24->TabIndex = 33;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(18, 146);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(51, 16);
			this->label25->TabIndex = 32;
			this->label25->Text = L"min|S|=";
			// 
			// textBox23
			// 
			this->textBox23->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox23->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox23->Location = System::Drawing::Point(70, 127);
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(159, 15);
			this->textBox23->TabIndex = 31;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(18, 127);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(55, 16);
			this->label24->TabIndex = 30;
			this->label24->Text = L"max|S|=";
			// 
			// textBox22
			// 
			this->textBox22->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox22->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox22->Location = System::Drawing::Point(55, 108);
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(170, 15);
			this->textBox22->TabIndex = 29;
			this->textBox22->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox22_TextChanged);
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(18, 108);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(43, 16);
			this->label23->TabIndex = 28;
			this->label23->Text = L"b-xN=";
			// 
			// textBox21
			// 
			this->textBox21->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox21->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox21->Location = System::Drawing::Point(285, 88);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(158, 15);
			this->textBox21->TabIndex = 27;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(222, 87);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(68, 16);
			this->label22->TabIndex = 26;
			this->label22->Text = L"vN_итог=";
			// 
			// textBox20
			// 
			this->textBox20->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox20->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox20->Location = System::Drawing::Point(45, 90);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(171, 15);
			this->textBox20->TabIndex = 25;
			this->textBox20->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox20_TextChanged);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(19, 90);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(31, 16);
			this->label21->TabIndex = 24;
			this->label21->Text = L"xN=";
			// 
			// textBox18
			// 
			this->textBox18->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox18->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox18->Location = System::Drawing::Point(550, 45);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(101, 15);
			this->textBox18->TabIndex = 22;
			this->textBox18->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox18_TextChanged);
			// 
			// textBox19
			// 
			this->textBox19->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox19->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox19->Location = System::Drawing::Point(376, 45);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(102, 15);
			this->textBox19->TabIndex = 21;
			this->textBox19->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox19_TextChanged);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(487, 44);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(67, 16);
			this->label20->TabIndex = 20;
			this->label20->Text = L"eps(min)=";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(343, 44);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(38, 16);
			this->label19->TabIndex = 18;
			this->label19->Text = L"eps=";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(19, 23);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(150, 16);
			this->label12->TabIndex = 5;
			this->label12->Text = L"Тип задачи: тестовая";
			// 
			// textBox10
			// 
			this->textBox10->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->textBox10->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox10->Location = System::Drawing::Point(215, 67);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(58, 15);
			this->textBox10->TabIndex = 2;
			this->textBox10->TextChanged += gcnew System::EventHandler(this, &Task11_Mironova::textBox10_TextChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(19, 67);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(200, 16);
			this->label9->TabIndex = 0;
			this->label9->Text = L"Кол-во совершенных шагов N:";
			this->label9->Click += gcnew System::EventHandler(this, &Task11_Mironova::label9_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox1->Location = System::Drawing::Point(8, 151);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(250, 20);
			this->checkBox1->TabIndex = 23;
			this->checkBox1->Text = L"Контроль локальной погрешности";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label38->Location = System::Drawing::Point(6, 51);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(16, 16);
			this->label38->TabIndex = 30;
			this->label38->Text = L"g";
			// 
			// textBox37
			// 
			this->textBox37->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox37->Location = System::Drawing::Point(28, 49);
			this->textBox37->Name = L"textBox37";
			this->textBox37->Size = System::Drawing::Size(137, 22);
			this->textBox37->TabIndex = 31;
			this->textBox37->Text = L"9,8";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label39->ForeColor = System::Drawing::SystemColors::InfoText;
			this->label39->Location = System::Drawing::Point(6, 77);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(19, 16);
			this->label39->TabIndex = 32;
			this->label39->Text = L"m";
			this->label39->Click += gcnew System::EventHandler(this, &Task11_Mironova::label39_Click);
			// 
			// textBox38
			// 
			this->textBox38->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox38->Location = System::Drawing::Point(28, 74);
			this->textBox38->Name = L"textBox38";
			this->textBox38->Size = System::Drawing::Size(137, 22);
			this->textBox38->TabIndex = 33;
			this->textBox38->Text = L"1";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label40->Location = System::Drawing::Point(6, 75);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(128, 16);
			this->label40->TabIndex = 34;
			this->label40->Text = L"Макс. число шагов";
			// 
			// textBox39
			// 
			this->textBox39->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox39->Location = System::Drawing::Point(261, 72);
			this->textBox39->Name = L"textBox39";
			this->textBox39->Size = System::Drawing::Size(159, 22);
			this->textBox39->TabIndex = 35;
			this->textBox39->Text = L"3000";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox44);
			this->groupBox2->Controls->Add(this->label46);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->textBox9);
			this->groupBox2->Controls->Add(this->label40);
			this->groupBox2->Controls->Add(this->textBox39);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->textBox4);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->checkBox1);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox2->Location = System::Drawing::Point(12, 46);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(433, 177);
			this->groupBox2->TabIndex = 36;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Параметры метода";
			// 
			// textBox44
			// 
			this->textBox44->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox44->Location = System::Drawing::Point(261, 122);
			this->textBox44->Name = L"textBox44";
			this->textBox44->Size = System::Drawing::Size(159, 22);
			this->textBox44->TabIndex = 37;
			this->textBox44->Text = L"0,001";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label46->Location = System::Drawing::Point(5, 125);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(249, 16);
			this->label46->TabIndex = 36;
			this->label46->Text = L"Точность выхода на правую границу";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->textBox8);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->textBox7);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->textBox6);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox3->Location = System::Drawing::Point(456, 46);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(178, 105);
			this->groupBox3->TabIndex = 37;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Начальные условия";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox38);
			this->groupBox4->Controls->Add(this->label39);
			this->groupBox4->Controls->Add(this->textBox37);
			this->groupBox4->Controls->Add(this->label38);
			this->groupBox4->Controls->Add(this->textBox5);
			this->groupBox4->Controls->Add(this->label4);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox4->Location = System::Drawing::Point(456, 157);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(178, 105);
			this->groupBox4->TabIndex = 38;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Параметры задачи";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->button1->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(11, 9);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(138, 32);
			this->button1->TabIndex = 39;
			this->button1->Text = L"Описание задачи";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Task11_Mironova::button1_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->button4->FlatAppearance->BorderColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(155, 8);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(167, 32);
			this->button4->TabIndex = 40;
			this->button4->Text = L"Используемый метод";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Task11_Mironova::button4_Click);
			// 
			// chart3
			// 
			chartArea3->Name = L"ChartArea1";
			this->chart3->ChartAreas->Add(chartArea3);
			legend3->Alignment = System::Drawing::StringAlignment::Center;
			legend3->AutoFitMinFontSize = 10;
			legend3->BackImageAlignment = System::Windows::Forms::DataVisualization::Charting::ChartImageAlignmentStyle::Center;
			legend3->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Top;
			legend3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			legend3->IsTextAutoFit = false;
			legend3->ItemColumnSpacing = 10;
			legend3->MaximumAutoSize = 35;
			legend3->Name = L"Legend1";
			this->chart3->Legends->Add(legend3);
			this->chart3->Location = System::Drawing::Point(-24, 549);
			this->chart3->Name = L"chart3";
			series5->BorderWidth = 2;
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series5->Legend = L"Legend1";
			series5->Name = L"Численная траектория";
			series6->ChartArea = L"ChartArea1";
			series6->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series6->Legend = L"Legend1";
			series6->Name = L"Истинная траектория";
			this->chart3->Series->Add(series5);
			this->chart3->Series->Add(series6);
			this->chart3->Size = System::Drawing::Size(671, 375);
			this->chart3->TabIndex = 24;
			this->chart3->Text = L"chart3";
			title3->Alignment = System::Drawing::ContentAlignment::TopCenter;
			title3->BackColor = System::Drawing::Color::White;
			title3->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			title3->Name = L"Зависимость u\' от x";
			title3->Text = L"Зависимость угловой скорости маятника от времени u\'(x)";
			this->chart3->Titles->Add(title3);
			this->chart3->Click += gcnew System::EventHandler(this, &Task11_Mironova::chart3_Click);
			// 
			// Task11_Mironova
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(1351, 921);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->chart3);
			this->Controls->Add(this->groupBox2);
			this->Name = L"Task11_Mironova";
			this->Text = L"Команда 1. Задача 11, вариант 2. Миронова E. ";
			this->Load += gcnew System::EventHandler(this, &Task11_Mironova::Task11_Mironova_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) { //график u от х
		this->dataGridView1->Rows->Clear();
		std::vector<double> x,u1,u2; //истинная траектория
		std::vector<double> v1, v2; //численная траектория
		std::vector<double> hn; //численная траектория
		std::vector<double> characteristics_with_control_lp; //S*, Vудв, V'удв
		double a1,a2,a;//переменные, в которых рассчитывается истинное решение, а=g/L
		double c1, c2;//коэффициенты для решения задачи Коши
		double L = 0.1, g=9.8, m=1;
		double NMAX = 10000;
		double E1max = 0, xE1max, E2max = 0, xE2max;//оценка глобальной погрешности
		int n = 0,k; //номер шага, коэффициент изменения шага (для подсчета числа ум/ув шага)
		double v1_0 = PI / 10, x0 = 0, v2_0 = 0, eps_gr=10E-4; //начальные условия и eps(гр)
		double  S_, S_min=1, S_max=0, xS_min, xS_max;
		int increase_h=0, decrease_h=0; //кол-во увеличений и уменьшений шага
		double h_min, h_max=0,xh_max,xh_min;
		bool f = checkBox1->Checked; //выбран ли контроль лп 
		x0= Convert::ToDouble(this->textBox6->Text);
		v1_0 = Convert::ToDouble(this->textBox7->Text);
		v2_0 = Convert::ToDouble(this->textBox8->Text);
		eps_gr= Convert::ToDouble(this->textBox44->Text);
		x.push_back(x0);
		v1.push_back(v1_0);
		u1.push_back(v1_0);
		v2.push_back(v2_0);
		u2.push_back(v2_0);
		double h,h0=0.001,b=1,eps=1E-6,h_prev; //шаг, начальный шаг, правая граница, параметр контроля eps, предыдущий шаг
		m= Convert::ToDouble(this->textBox38->Text);
		h0 = Convert::ToDouble(this->textBox3->Text);
		h = h0;
		h_min = h0;
		h_prev = h;
		hn.push_back(h0);
		b = Convert::ToDouble(this->textBox9->Text);
		L= Convert::ToDouble(this->textBox5->Text);
		NMAX = Convert::ToDouble(this->textBox39->Text);
		g = Convert::ToDouble(this->textBox37->Text);
		if ((f==1)&& (this->textBox4->Text != ""))
			eps = Convert::ToDouble(this->textBox4->Text);
		this->chart1->ChartAreas[0]->AxisX->Maximum = b;
		this->chart3->ChartAreas[0]->AxisX->Maximum = b;
		this->dataGridView1->Rows->Add(0, " ", x0, v1_0, v2_0," ", " ", " ", v1_0,v2_0,0,0," "," ");
		a = g / L;
		//рассчет коэффициентов для решения задачи Коши
		c1 = (v2_0 / sqrt(a) + v1_0 * tan(sqrt(a) * x0)) / (cos(sqrt(a) * x0) + sin(sqrt(a) * x0) * tan(sqrt(a) * x0));
		c2 = v1_0 / cos(sqrt(a) * x0) - c1 * tan(sqrt(a) * x0);
		int i=1, i_prev=1;
		while (i<=NMAX){
			i_prev = i;
			if ((x[n] >= b - eps_gr)||(x[n]>=b)) break;
			if (f == 1) {
				h_prev = h;
				characteristics_with_control_lp = method_RK_4_with_control_lp(L,g, n, x, v1, v2, h, eps);
				if (x[i] > b) {
					x.pop_back();
					v1.pop_back();
					v2.pop_back();
					h = h_prev/2;
					n--;
					i--;
				}
				
				if (h_prev > h) {
					k = int(h_prev / h)/2;
					decrease_h+=k;
				}
				if (h_prev < h) {
					k = int(h / h_prev) / 2;
					increase_h+=k;
				}
				if (characteristics_with_control_lp[3] >= S_max) {
					S_max = characteristics_with_control_lp[3];
					xS_max = x[i];
				}
				if (characteristics_with_control_lp[3] <= S_min) {
					S_min = characteristics_with_control_lp[3];
					xS_min = x[i];
				}
				if (h >= h_max) {
					h_max = h;
					xh_max = x[i];
				}
				if (h <= h_min) {
					h_min = h;
					xh_min = x[i];
				}
			}
			else {
				method_RK_4(L,g, n, x, v1, v2, h);
				if (x[i] > b) {
					x.pop_back();
					v1.pop_back();
					v2.pop_back();
					h = h_prev/2;
					n--;
					i--;
				}

			}
			a1 = c1 * sin(sqrt(a) * x[i]) + c2 * cos(sqrt(a) * x[i]);
			a2= sqrt(a)*(c1 * cos(sqrt(a) * x[i]) - c2 * sin(sqrt(a) * x[i]));
			u1.push_back(a1);
			u2.push_back(a2);
			if (i_prev == i) {
				if (f == 1)
					this->dataGridView1->Rows->Add(i, h, x[i], v1[i], v2[i], characteristics_with_control_lp[1], characteristics_with_control_lp[2], characteristics_with_control_lp[0], u1[i], u2[i], abs(u1[i] - v1[i]), abs(u2[i] - v2[i]), h_prev > h, h_prev < h);
				else
					this->dataGridView1->Rows->Add(i, h, x[i], v1[i], v2[i], "-", "-", "-", u1[i], u2[i], abs(u1[i] - v1[i]), abs(u2[i] - v2[i]), "-", "-");
			}
			if (E1max < abs(u1[i] - v1[i])) {
				E1max = abs(u1[i] - v1[i]);
				xE1max = x[i];
			}
			if (E2max < abs(u2[i] - v2[i])) {
				E2max = abs(u2[i] - v2[i]);
				xE2max = x[i];
			}
			i++;
		}
		double s= b - x[n-1];
		for (int i = 0; i < x.size(); i++) {
			this->chart1->Series[1]->Points->AddXY(x[i], u1[i]);
			this->chart1->Series[0]->Points->AddXY(x[i], v1[i]);
			this->chart3->Series[0]->Points->AddXY(x[i], v2[i]);
			this->chart3->Series[1]->Points->AddXY(x[i], u2[i]);
			this->chart2->Series[0]->Points->AddXY(v1[i], v2[i]);
			this->chart2->Series[1]->Points->AddXY(u1[i], u2[i]);
		}

		this->textBox10->Text = (n).ToString();
		this->textBox20->Text = (x[x.size() - 1]).ToString();
		this->textBox21->Text = (v1[v1.size()-1]).ToString();
		this->textBox22->Text = (b-x[x.size() -1]).ToString();
		this->textBox33->Text = (v2[v2.size() - 1]).ToString();
		this->textBox35->Text = (E1max).ToString();
		this->textBox36->Text = (xE1max).ToString();
		this->textBox41->Text = (E2max).ToString();
		this->textBox42->Text = (xE2max).ToString();
		if (f == 1) {
			this->textBox32->Text = (decrease_h).ToString(); //кол-во уменьшений шага
			this->textBox31->Text = (increase_h).ToString(); //кол-во увеличений шага
			this->textBox18->Text = (eps / 32).ToString(); //eps_min=eps/(2^(p+1))
			this->textBox19->Text = (eps).ToString(); //eps
			this->textBox23->Text = (S_max).ToString();//max|S|
			this->textBox25->Text = (xS_max).ToString();//при xn=...
			this->textBox24->Text = (S_min).ToString();//min|S|
			this->textBox26->Text = (xS_min).ToString();//при xn=...
			this->textBox27->Text = (h_max).ToString();//max_h
			this->textBox28->Text = (xh_max).ToString();//при xn=...
			this->textBox29->Text = (h_min).ToString();//min_h
			this->textBox30->Text = (xh_min).ToString();//при xn=...
			this->textBox11->Text = "включен";
		}
		else {
			this->textBox32->Text = "";
			this->textBox31->Text = "";
			this->textBox18->Text = "";
			this->textBox19->Text = "";
			this->textBox23->Text = "";
			this->textBox25->Text = "";
			this->textBox24->Text = "";
			this->textBox26->Text = "";
			this->textBox27->Text = "";
			this->textBox28->Text = "";
			this->textBox29->Text = "";
			this->textBox30->Text = "";
			this->textBox11->Text = "выключен";
		}

		// Добавлем фиктивную точку
		this->chart1->Series[0]->Points->AddXY(x[x.size() - 1], v1[x.size() - 1]);
		this->chart1->Series[1]->Points->AddXY(x[x.size() - 1], u1[x.size() - 1]);
		this->chart3->Series[0]->Points->AddXY(x[x.size() - 1], v2[x.size() - 1]);
		this->chart3->Series[1]->Points->AddXY(x[x.size() - 1], u2[x.size() - 1]);
		this->chart2->Series[0]->Points->AddXY(v1[v1.size() - 1], v2[v2.size() - 1]);
		this->chart2->Series[1]->Points->AddXY(u1[u1.size() - 1], u2[u2.size() - 1]);
		// Делаем ее невидимой

		int count = this->chart1->Series[0]->Points->Count;
		this->chart1->Series[0]->Points[count - 1]->IsEmpty = true;
		count = this->chart1->Series[1]->Points->Count;
		this->chart1->Series[1]->Points[count - 1]->IsEmpty = true;

		count = this->chart3->Series[0]->Points->Count;
		this->chart3->Series[0]->Points[count - 1]->IsEmpty = true;
		count = this->chart3->Series[1]->Points->Count;
		this->chart3->Series[1]->Points[count - 1]->IsEmpty = true;

		count = this->chart2->Series[0]->Points->Count;
		this->chart2->Series[0]->Points[count - 1]->IsEmpty = true;
		count = this->chart2->Series[1]->Points->Count;
		this->chart2->Series[1]->Points[count - 1]->IsEmpty = true;
		

	}

		private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {//очистка первого графика и таблицы
			this->chart1->Series[0]->Points->Clear();
			this->chart1->Series[1]->Points->Clear();
			this->chart2->Series[0]->Points->Clear();
			this->chart2->Series[1]->Points->Clear();
			this->chart3->Series[0]->Points->Clear();
			this->chart3->Series[1]->Points->Clear();
			this->dataGridView1->Rows->Clear();
		}
		private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
		}

		private: System::Void dataGridView1_CellContentClick_1(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		}

		private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
		}

		private: System::Void chart2_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) { //начальный шаг
		}
		private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) { //eps ввод
		}
		private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) { //N ввод
		}
		private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e) { //x0 ввод
		}
		private: System::Void textBox7_TextChanged(System::Object^ sender, System::EventArgs^ e) {//u(0) ввод
		}
		private: System::Void textBox8_TextChanged(System::Object^ sender, System::EventArgs^ e) {//u'(0) ввод
		}
		private: System::Void textBox9_TextChanged(System::Object^ sender, System::EventArgs^ e) { //b ввод
		}
		private: System::Void chart3_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void dataGridView2_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		}
		private: System::Void label9_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void label10_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void textBox10_TextChanged(System::Object^ sender, System::EventArgs^ e) { //кол-во итераций
		}
		private: System::Void textBox11_TextChanged(System::Object^ sender, System::EventArgs^ e) { //макс. кол-во итераций
		}
		private: System::Void label11_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void label13_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void textBox22_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void textBox12_TextChanged(System::Object^ sender, System::EventArgs^ e) { //х0
		}
		private: System::Void textBox13_TextChanged(System::Object^ sender, System::EventArgs^ e) { //u(0)
		}
		private: System::Void textBox14_TextChanged(System::Object^ sender, System::EventArgs^ e) { //u'(0)
		}
		private: System::Void textBox15_TextChanged(System::Object^ sender, System::EventArgs^ e) { //h0
		}
		private: System::Void textBox16_TextChanged(System::Object^ sender, System::EventArgs^ e) { //b
		}
		private: System::Void textBox17_TextChanged(System::Object^ sender, System::EventArgs^ e) { //eps(гр)
		}
		private: System::Void textBox19_TextChanged(System::Object^ sender, System::EventArgs^ e) { //eps
		}
		private: System::Void textBox18_TextChanged(System::Object^ sender, System::EventArgs^ e) { //eps(min)
		}
		private: System::Void textBox20_TextChanged(System::Object^ sender, System::EventArgs^ e) { //vN
		}
		private: System::Void textBox33_TextChanged(System::Object^ sender, System::EventArgs^ e) {//v'N
		}
private: System::Void label32_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox31_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox27_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label35_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label39_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox36_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Task11_Mironova_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	Task^ form1 = gcnew Task();
	form1->Show();
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	Method^ form2 = gcnew Method();
	form2->Show();
}
private: System::Void textBox35_TextChanged(System::Object^ sender, System::EventArgs^ e) {






































}
};
}

