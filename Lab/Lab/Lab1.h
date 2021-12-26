#pragma once
#include <vector>
#include <cmath>

double f1(double x, double u) {
	return -u/2;
}

double f2(double x, double u) {
	return u*u/(1+pow(x,4))+u-pow(u,3)*sin(10*x);
}

double f3(double x, double u1, double u2) {
	return u2;
}

double f4(double x, double u1, double u2, double a) {
	return -a*sin(u1);
}

std::vector<double> method_RK_4_count(double (*f1)(double,double),double x, double v, double h) { //(7) в методичке
	double k1, k2, k3, k4;
	std::vector<double> result;
	k1 = f1(x, v);
	k2 = f1(x + h / 2, v + h * k1 / 2);
	k3 = f1(x + h / 2, v + h * k2 / 2);
	k4 = f1(x + h, v + h * k3);
	result.push_back(x + h);//x[n+1]
	result.push_back(v + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6);//v[n+1]
	return result;
}

void method_RK_4(double (*f1)(double, double), int& n, std::vector<double>& x, std::vector<double>& v, double& h) {
	std::vector<double> result;
	result = method_RK_4_count(f1,x[n], v[n], h);
	x.push_back(result[0]);
	v.push_back(result[1]);
	n++;
}

std::vector<double> method_RK_4_with_control_lp(double (*f1)(double, double), int& n, std::vector<double>& x, std::vector<double>& v, double& h, double eps, int& inc_h, int& dec_h, double& max_olp, double b) {
	std::vector<double> characteristics_for_table(2); //[S*,Vудв]
	std::vector<double> result1, result2;//[xn,Vn]
	double x_12 = x[n], v_12 = v[n];
	bool f = 0;
	if (x[n] + h > b) {
		h = b - x[n];
		dec_h++;
		f = 1;
	}
	result1 = method_RK_4_count(f1,x[n], v[n],  h); //решение методом РК с шагом h
	result2 = method_RK_4_count(f1,x_12, v_12, h / 2);
	result2 = method_RK_4_count(f1,result2[0], result2[1], h / 2); //решение с половинными шагом
	double S;
	S = (result2[1] - result1[1]) / 15;
	if ((abs(S) >= eps / 32) && (abs(S) <= eps)) {
		x.push_back(result1[0]);
		v.push_back(result1[1]);
		n++;
	}
	if (abs(S) < eps / 32) {
		x.push_back(result1[0]);
		v.push_back(result1[1]);
		if (f != 1) {
			h *= 2;
			inc_h++;
		}
		n++;
	}
	if (abs(S) > eps) {
		h = h / 2;
		dec_h++;
		return method_RK_4_with_control_lp(f1,n, x, v, h, eps, inc_h, dec_h, max_olp,b);
	}
	characteristics_for_table[0] = S * 16;
	characteristics_for_table[1] = result2[1];
	if (abs(S * 16) > max_olp)
		max_olp = abs(S * 16);
	return characteristics_for_table;
}

std::vector<double> method_RK_4_count_for_system(double (*f1)(double, double, double), double (*f2)(double, double, double,double), double a, double x, double v1, double v2, double h) { //(7) в методичке
	double k1[2], k2[2], k3[2], k4[2];
	std::vector<double> result;
	k1[0] = f1(x, v1, v2);
	k1[1] = f2(x, v1, v2,a);
	k2[0] = f1(x + h / 2, v1 + h * k1[0] / 2, v2 + h * k1[1] / 2);
	k2[1] = f2(x + h / 2, v1 + h * k1[0] / 2, v2 + h * k1[1] / 2,a);
	k3[0] = f1(x + h / 2, v1 + h * k2[0] / 2, v2 + h * k2[1] / 2);
	k3[1] = f2(x + h / 2, v1 + h * k2[0] / 2, v2 + h * k2[1] / 2,a);
	k4[0] = f1(x + h, v1 + h * k3[0], v2 + h * k3[1]);
	k4[1] = f2(x + h, v1 + h * k3[0], v2 + h * k3[1],a);
	result.push_back(x + h);//x[n+1]
	result.push_back(v1 + h * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]) / 6);//v1[n+1]
	result.push_back(v2 + h * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) / 6);//v2[n+1]
	return result;
}

void method_RK_4_for_system(double (*f1)(double, double, double), double (*f2)(double, double, double, double), double a, int& n, std::vector<double>& x, std::vector<double>& v1, std::vector<double>& v2, double& h) {
	std::vector<double> result;
	result = method_RK_4_count_for_system(f1, f2, a, x[n], v1[n], v2[n], h);
	x.push_back(result[0]);
	v1.push_back(result[1]);
	v2.push_back(result[2]);
	n++;
}


std::vector<double> method_RK_4_with_control_lp_for_system(double (*f1)(double, double, double), double (*f2)(double, double, double, double), double a, int& n, std::vector<double>& x, std::vector<double>& v1, std::vector<double>& v2, double& h, double eps, int& inc_h, int& dec_h, double& max_olp, double b) {
	std::vector<double> characteristics_for_table(2); //[S*,Vудв]
	std::vector<double> result1, result2;//[xn,Vn,V'n]
	double x_12 = x[n], v1_12 = v1[n], v2_12 = v2[n];
	bool f = 0;
	if (x[n] + h > b) {
		h = b - x[n];
		dec_h++;
		f = 1;
	}
	result1 = method_RK_4_count_for_system(f1, f2, a, x[n], v1[n], v2[n], h); //решение методом РК с шагом h
	result2 = method_RK_4_count_for_system(f1, f2, a, x_12, v1_12, v2_12, h / 2);
	result2 = method_RK_4_count_for_system(f1, f2, a, result2[0], result2[1], result2[2], h / 2); //решение с половинными шагом
	double S, S1, S2;
	S1 = (result2[1] - result1[1]) / 15;
	S2 = (result2[2] - result1[2]) / 15;
	S = std::max(abs(S1), abs(S2));
	if ((abs(S) >= eps / 32) && (abs(S) <= eps)) {
		x.push_back(result1[0]);
		v1.push_back(result1[1]);
		v2.push_back(result1[2]);
		n++;
	}
	if (abs(S) < eps / 32) {
		x.push_back(result1[0]);
		v1.push_back(result1[1]);
		v2.push_back(result1[2]);
		if (f != 1) {
			h *= 2;
			inc_h++;
		}
		n++;
	}
	if (abs(S) > eps) {
		h = h / 2;
		dec_h++;
		return method_RK_4_with_control_lp_for_system(f1, f2, a, n, x, v1, v2, h, eps, inc_h, dec_h, max_olp,b);
	}
	if (abs(S * 16) > max_olp)
		max_olp = abs(S * 16);
	characteristics_for_table[0] = S * 16;
	characteristics_for_table[1] = result2[1];
	return characteristics_for_table;
}


namespace Lab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Lab1
	/// </summary>
	public ref class Lab1 : public System::Windows::Forms::Form
	{
	public:
		Lab1(void)
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
		~Lab1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ Table_for_test_task;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column10;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column11;
	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ u0;

	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::TextBox^ eps_gr;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ b;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ eps;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ Nmax;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ h0;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::TextBox^ x_max_ui_vi;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::TextBox^ max_ui_vi;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::TextBox^ x_h_min;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ min_h;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TextBox^ x_h_max;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ max_h;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ dec_h;
	private: System::Windows::Forms::TextBox^ inc_h;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ max_olp;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ b_xN;
	private: System::Windows::Forms::Label^ label12;




	private: System::Windows::Forms::TextBox^ n;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ u0_pr;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ vN;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ xN;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::TextBox^ a;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label22;



	//private: System::Diagnostics::PerformanceCounter^ performanceCounter1;



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Lab1::typeid));
			this->Table_for_test_task = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->a = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->u0_pr = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->u0 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->eps_gr = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->b = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->eps = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->Nmax = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->h0 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->x_max_ui_vi = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->max_ui_vi = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->x_h_min = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->min_h = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->x_h_max = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->max_h = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->dec_h = (gcnew System::Windows::Forms::TextBox());
			this->inc_h = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->max_olp = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->b_xN = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->vN = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->xN = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->n = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Table_for_test_task))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// Table_for_test_task
			// 
			this->Table_for_test_task->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Table_for_test_task->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(11) {
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8, this->Column9, this->Column10,
					this->Column11
			});
			this->Table_for_test_task->Location = System::Drawing::Point(2, 301);
			this->Table_for_test_task->Name = L"Table_for_test_task";
			this->Table_for_test_task->Size = System::Drawing::Size(619, 457);
			this->Table_for_test_task->TabIndex = 0;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"№";
			this->Column1->Name = L"Column1";
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"xi";
			this->Column2->Name = L"Column2";
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"vi";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"v2i";
			this->Column4->Name = L"Column4";
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"vi-v2i";
			this->Column5->Name = L"Column5";
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"ОЛП";
			this->Column6->Name = L"Column6";
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"hi";
			this->Column7->Name = L"Column7";
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"C1";
			this->Column8->Name = L"Column8";
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"C2";
			this->Column9->Name = L"Column9";
			// 
			// Column10
			// 
			this->Column10->HeaderText = L"ui";
			this->Column10->Name = L"Column10";
			// 
			// Column11
			// 
			this->Column11->HeaderText = L"|ui-vi|";
			this->Column11->Name = L"Column11";
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			legend1->TitleAlignment = System::Drawing::StringAlignment::Near;
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(608, 278);
			this->chart1->Name = L"chart1";
			series1->BorderWidth = 4;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Legend = L"Legend1";
			series1->Name = L"Численная траектория";
			series2->BorderWidth = 2;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->LabelBorderWidth = 3;
			series2->Legend = L"Legend1";
			series2->Name = L"Истинная траектория";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(695, 480);
			this->chart1->TabIndex = 1;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Lab1::chart1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->groupBox1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->Location = System::Drawing::Point(296, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->groupBox1->Size = System::Drawing::Size(325, 59);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"ДУ";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(6, 16);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(313, 40);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label22);
			this->groupBox2->Controls->Add(this->a);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->u0_pr);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->u0);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox2->Location = System::Drawing::Point(448, 71);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(173, 127);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Начальные условия";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(6, 80);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(140, 16);
			this->label22->TabIndex = 8;
			this->label22->Text = L"Параметр задачи";
			// 
			// a
			// 
			this->a->BackColor = System::Drawing::SystemColors::MenuBar;
			this->a->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->a->Location = System::Drawing::Point(37, 99);
			this->a->Name = L"a";
			this->a->Size = System::Drawing::Size(117, 22);
			this->a->TabIndex = 7;
			this->a->Text = L"1";
			this->a->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(9, 101);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(16, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"a";
			this->label2->Visible = false;
			// 
			// u0_pr
			// 
			this->u0_pr->BackColor = System::Drawing::SystemColors::MenuBar;
			this->u0_pr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->u0_pr->Location = System::Drawing::Point(37, 54);
			this->u0_pr->Name = L"u0_pr";
			this->u0_pr->Size = System::Drawing::Size(117, 22);
			this->u0_pr->TabIndex = 5;
			this->u0_pr->Text = L"1";
			this->u0_pr->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(9, 57);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(25, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"u\'0";
			this->label1->Visible = false;
			// 
			// u0
			// 
			this->u0->BackColor = System::Drawing::SystemColors::MenuBar;
			this->u0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->u0->Location = System::Drawing::Point(37, 26);
			this->u0->Name = L"u0";
			this->u0->Size = System::Drawing::Size(117, 22);
			this->u0->TabIndex = 3;
			this->u0->Text = L"1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(9, 29);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(22, 16);
			this->label3->TabIndex = 1;
			this->label3->Text = L"u0";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->checkBox1);
			this->groupBox3->Controls->Add(this->eps_gr);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->b);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->eps);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->Nmax);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->h0);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox3->Location = System::Drawing::Point(12, 70);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(430, 212);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Параметры метода";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox1->Location = System::Drawing::Point(9, 156);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(250, 20);
			this->checkBox1->TabIndex = 13;
			this->checkBox1->Text = L"Контроль локальной погрешности";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// eps_gr
			// 
			this->eps_gr->BackColor = System::Drawing::SystemColors::MenuBar;
			this->eps_gr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->eps_gr->Location = System::Drawing::Point(311, 127);
			this->eps_gr->Name = L"eps_gr";
			this->eps_gr->Size = System::Drawing::Size(108, 22);
			this->eps_gr->TabIndex = 12;
			this->eps_gr->Text = L"0,1";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(6, 128);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(299, 16);
			this->label8->TabIndex = 11;
			this->label8->Text = L"Контроль выхода на правую границу, eps_гр";
			// 
			// b
			// 
			this->b->BackColor = System::Drawing::SystemColors::MenuBar;
			this->b->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->b->Location = System::Drawing::Point(311, 101);
			this->b->Name = L"b";
			this->b->Size = System::Drawing::Size(108, 22);
			this->b->TabIndex = 10;
			this->b->Text = L"5";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(6, 101);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(182, 16);
			this->label7->TabIndex = 9;
			this->label7->Text = L"Правая граница по оси x, b";
			// 
			// eps
			// 
			this->eps->BackColor = System::Drawing::SystemColors::MenuBar;
			this->eps->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->eps->Location = System::Drawing::Point(311, 75);
			this->eps->Name = L"eps";
			this->eps->Size = System::Drawing::Size(108, 22);
			this->eps->TabIndex = 8;
			this->eps->Text = L"1E-10";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(6, 78);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(189, 16);
			this->label6->TabIndex = 7;
			this->label6->Text = L"Параметр контроля ЛП, eps";
			// 
			// Nmax
			// 
			this->Nmax->BackColor = System::Drawing::SystemColors::MenuBar;
			this->Nmax->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Nmax->Location = System::Drawing::Point(311, 49);
			this->Nmax->Name = L"Nmax";
			this->Nmax->Size = System::Drawing::Size(108, 22);
			this->Nmax->TabIndex = 6;
			this->Nmax->Text = L"10000";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(6, 52);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(128, 16);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Макс. число шагов";
			// 
			// h0
			// 
			this->h0->BackColor = System::Drawing::SystemColors::MenuBar;
			this->h0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->h0->Location = System::Drawing::Point(311, 24);
			this->h0->Name = L"h0";
			this->h0->Size = System::Drawing::Size(108, 22);
			this->h0->TabIndex = 4;
			this->h0->Text = L"0,001";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(6, 27);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(128, 16);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Начальный шаг, h0";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button1->Location = System::Drawing::Point(448, 204);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(173, 34);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Запуск";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Lab1::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->button2->Location = System::Drawing::Point(448, 244);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(173, 36);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Очистка";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Lab1::button2_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->groupBox4->Controls->Add(this->x_max_ui_vi);
			this->groupBox4->Controls->Add(this->label21);
			this->groupBox4->Controls->Add(this->max_ui_vi);
			this->groupBox4->Controls->Add(this->label20);
			this->groupBox4->Controls->Add(this->x_h_min);
			this->groupBox4->Controls->Add(this->label19);
			this->groupBox4->Controls->Add(this->min_h);
			this->groupBox4->Controls->Add(this->label18);
			this->groupBox4->Controls->Add(this->x_h_max);
			this->groupBox4->Controls->Add(this->label17);
			this->groupBox4->Controls->Add(this->max_h);
			this->groupBox4->Controls->Add(this->label16);
			this->groupBox4->Controls->Add(this->dec_h);
			this->groupBox4->Controls->Add(this->inc_h);
			this->groupBox4->Controls->Add(this->label15);
			this->groupBox4->Controls->Add(this->label14);
			this->groupBox4->Controls->Add(this->max_olp);
			this->groupBox4->Controls->Add(this->label13);
			this->groupBox4->Controls->Add(this->b_xN);
			this->groupBox4->Controls->Add(this->label12);
			this->groupBox4->Controls->Add(this->vN);
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->xN);
			this->groupBox4->Controls->Add(this->label10);
			this->groupBox4->Controls->Add(this->n);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox4->Location = System::Drawing::Point(632, 12);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(632, 270);
			this->groupBox4->TabIndex = 7;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Справка";
			// 
			// x_max_ui_vi
			// 
			this->x_max_ui_vi->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->x_max_ui_vi->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->x_max_ui_vi->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->x_max_ui_vi->Location = System::Drawing::Point(298, 243);
			this->x_max_ui_vi->Name = L"x_max_ui_vi";
			this->x_max_ui_vi->Size = System::Drawing::Size(153, 15);
			this->x_max_ui_vi->TabIndex = 28;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(254, 242);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(48, 16);
			this->label21->TabIndex = 27;
			this->label21->Text = L"при x=";
			// 
			// max_ui_vi
			// 
			this->max_ui_vi->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->max_ui_vi->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->max_ui_vi->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->max_ui_vi->Location = System::Drawing::Point(79, 244);
			this->max_ui_vi->Name = L"max_ui_vi";
			this->max_ui_vi->Size = System::Drawing::Size(169, 15);
			this->max_ui_vi->TabIndex = 26;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(15, 243);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(70, 16);
			this->label20->TabIndex = 25;
			this->label20->Text = L"max|ui-vi|=";
			// 
			// x_h_min
			// 
			this->x_h_min->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->x_h_min->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->x_h_min->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->x_h_min->Location = System::Drawing::Point(273, 215);
			this->x_h_min->Name = L"x_h_min";
			this->x_h_min->Size = System::Drawing::Size(148, 15);
			this->x_h_min->TabIndex = 24;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(230, 215);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(48, 16);
			this->label19->TabIndex = 23;
			this->label19->Text = L"при x=";
			// 
			// min_h
			// 
			this->min_h->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->min_h->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->min_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->min_h->Location = System::Drawing::Point(64, 215);
			this->min_h->Name = L"min_h";
			this->min_h->Size = System::Drawing::Size(160, 15);
			this->min_h->TabIndex = 22;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(15, 215);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(49, 16);
			this->label18->TabIndex = 21;
			this->label18->Text = L"min hi=";
			// 
			// x_h_max
			// 
			this->x_h_max->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->x_h_max->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->x_h_max->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->x_h_max->Location = System::Drawing::Point(273, 187);
			this->x_h_max->Name = L"x_h_max";
			this->x_h_max->Size = System::Drawing::Size(148, 15);
			this->x_h_max->TabIndex = 20;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(230, 187);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(48, 16);
			this->label17->TabIndex = 19;
			this->label17->Text = L"при x=";
			// 
			// max_h
			// 
			this->max_h->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->max_h->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->max_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->max_h->Location = System::Drawing::Point(64, 188);
			this->max_h->Name = L"max_h";
			this->max_h->Size = System::Drawing::Size(158, 15);
			this->max_h->TabIndex = 18;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(15, 187);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(53, 16);
			this->label16->TabIndex = 17;
			this->label16->Text = L"max hi=";
			// 
			// dec_h
			// 
			this->dec_h->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->dec_h->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dec_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->dec_h->Location = System::Drawing::Point(156, 160);
			this->dec_h->Name = L"dec_h";
			this->dec_h->Size = System::Drawing::Size(122, 15);
			this->dec_h->TabIndex = 16;
			// 
			// inc_h
			// 
			this->inc_h->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->inc_h->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->inc_h->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->inc_h->Location = System::Drawing::Point(164, 133);
			this->inc_h->Name = L"inc_h";
			this->inc_h->Size = System::Drawing::Size(114, 15);
			this->inc_h->TabIndex = 15;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(15, 159);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(144, 16);
			this->label15->TabIndex = 14;
			this->label15->Text = L"Число делений шага:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(15, 132);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(152, 16);
			this->label14->TabIndex = 13;
			this->label14->Text = L"Число удвоений шага:";
			// 
			// max_olp
			// 
			this->max_olp->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->max_olp->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->max_olp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->max_olp->Location = System::Drawing::Point(87, 105);
			this->max_olp->Name = L"max_olp";
			this->max_olp->Size = System::Drawing::Size(177, 15);
			this->max_olp->TabIndex = 12;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(15, 105);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(75, 16);
			this->label13->TabIndex = 11;
			this->label13->Text = L"max|OЛП|=";
			// 
			// b_xN
			// 
			this->b_xN->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->b_xN->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->b_xN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->b_xN->Location = System::Drawing::Point(55, 77);
			this->b_xN->Name = L"b_xN";
			this->b_xN->Size = System::Drawing::Size(167, 15);
			this->b_xN->TabIndex = 10;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(15, 77);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(43, 16);
			this->label12->TabIndex = 9;
			this->label12->Text = L"b-xN=";
			// 
			// vN
			// 
			this->vN->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->vN->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->vN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->vN->Location = System::Drawing::Point(238, 49);
			this->vN->Name = L"vN";
			this->vN->Size = System::Drawing::Size(162, 15);
			this->vN->TabIndex = 8;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(211, 49);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(32, 16);
			this->label11->TabIndex = 7;
			this->label11->Text = L"vN=";
			// 
			// xN
			// 
			this->xN->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->xN->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->xN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->xN->Location = System::Drawing::Point(43, 50);
			this->xN->Name = L"xN";
			this->xN->Size = System::Drawing::Size(162, 15);
			this->xN->TabIndex = 6;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(15, 50);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(31, 16);
			this->label10->TabIndex = 5;
			this->label10->Text = L"xN=";
			// 
			// n
			// 
			this->n->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->n->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->n->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->n->Location = System::Drawing::Point(217, 25);
			this->n->Name = L"n";
			this->n->Size = System::Drawing::Size(114, 15);
			this->n->TabIndex = 4;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(15, 25);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(207, 16);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Кол-во совершенных шагов, N=";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Тестовая задача", L"Основная задача 1", L"Основная задача 2" });
			this->comboBox1->Location = System::Drawing::Point(21, 26);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(251, 26);
			this->comboBox1->TabIndex = 8;
			this->comboBox1->Text = L"Тестовая задача";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Lab1::comboBox1_SelectedIndexChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"V(x)", L"V\'(x)", L"V\'(V)" });
			this->comboBox2->Location = System::Drawing::Point(1122, 328);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(59, 26);
			this->comboBox2->TabIndex = 9;
			this->comboBox2->Text = L"V(x)";
			this->comboBox2->Visible = false;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &Lab1::comboBox2_SelectedIndexChanged);
			// 
			// Lab1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(1279, 761);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->Table_for_test_task);
			this->Controls->Add(this->chart1);
			this->Name = L"Lab1";
			this->Text = L"Лабораторная работа №1. Команда 1: Цодиков, Миронова, Лабинская, Орлов";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Table_for_test_task))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void test() {
		this->Table_for_test_task->Rows->Clear();
		std::vector<double> x, u; //истинная траектория
		std::vector<double> v; //численная траектория
		std::vector<double> characteristics_with_control_lp; //S*, Vудв
		double c;//коэффициент для решения задачи Коши
		double NMAX;
		double Emax = 0, xEmax, max_olp = 0;//оценка глобальной и локальной погрешности
		int n = 0; //номер шага
		double v0, x0=0, eps_gr; //начальные условия и eps(гр)
		int increase_h = 0, decrease_h = 0;//кол-во увеличений и уменьшений шага
		int c1, c2;
		double h, b, eps, h_prev; //шаг, правая граница, параметр контроля eps, предыдущий шаг
		double h_min,h_max, xh_max, xh_min;
		bool f = checkBox1->Checked; //выбран ли контроль лп 
		v0 = Convert::ToDouble(this->u0->Text);
		x.push_back(x0);
		v.push_back(v0);
		u.push_back(v0);
		c = v0 / exp(-x0 / 2);
		h = Convert::ToDouble(this->h0->Text);
		h_prev = h;
		h_min = h;
		h_max = h;
		eps_gr = Convert::ToDouble(this->eps_gr->Text);
		b = Convert::ToDouble(this->b->Text);
		NMAX = Convert::ToDouble(this->Nmax->Text);
		if ((f == 1) && (this->eps->Text != ""))
			eps = Convert::ToDouble(this->eps->Text);
		this->chart1->ChartAreas[0]->AxisX->Minimum = 0;
		this->chart1->ChartAreas[0]->AxisX->Maximum = b;
		this->Table_for_test_task->Rows->Add(0, x0, v0, " ", " ", " ", h, "", "", v0, 0);

		int i = 1;
		while (i <= NMAX) {
			c1 = 0;
			c2 = 0;
			if ((x[n] > b - eps_gr) || (x[n] >= b)) break;
			if (f == 1) {
				h_prev = h;
				characteristics_with_control_lp = method_RK_4_with_control_lp(f1,n, x, v, h, eps, c2, c1, max_olp,b);
				if (c1 == c2) {
					c1 = 0;
					c2 = 0;
				}
				increase_h += c2;
				decrease_h += c1;
				if ((h >= h_max) || (i == 1)) {
					h_max = h;
					xh_max = x[i];
				}
				if ((h <= h_min)||(i==1)) {
					h_min = h;
					xh_min = x[i];
				}
			}
			else {
				method_RK_4(f1, n, x, v, h);
			}
			u.push_back(c * exp(-x[i] / 2));
			if (f == 1)
				this->Table_for_test_task->Rows->Add(i, x[i], v[i], characteristics_with_control_lp[1], v[i] - characteristics_with_control_lp[1], characteristics_with_control_lp[0], h, c1, c2, u[i], abs(u[i] - v[i]));
			else
				this->Table_for_test_task->Rows->Add(i, x[i], v[i], "-", "-", "-", h, "-", "-", u[i], abs(u[i] - v[i]));
			if (Emax < abs(u[i] - v[i])) {
				Emax = abs(u[i] - v[i]);
				xEmax = x[i];
			}
			i++;
		}
		for (int i = 0; i < x.size(); i++) {
			this->chart1->Series[1]->Points->AddXY(x[i], u[i]);
			this->chart1->Series[0]->Points->AddXY(x[i], v[i]);
		}

		this->n->Text = (n).ToString();
		this->xN->Text = (x[x.size() - 1]).ToString();
		this->vN->Text = (v[v.size() - 1]).ToString();
		this->b_xN->Text = (b - x[x.size() - 1]).ToString();
		this->max_ui_vi->Text = (Emax).ToString();
		this->x_max_ui_vi->Text = (xEmax).ToString();
		this->dec_h->Text = (decrease_h).ToString(); 
		this->inc_h->Text = (increase_h).ToString(); 
		this->max_olp->Text = (max_olp).ToString();
		if (f == 1) {
			this->max_h->Text = (h_max).ToString();
			this->x_h_max->Text = (xh_max).ToString();
			this->min_h->Text = (h_min).ToString();
			this->x_h_min->Text = (xh_min).ToString();
		}
		else {
			this->max_h->Text = (h_max).ToString();
			this->x_h_max->Text = "любой х";
			this->min_h->Text = (h_max).ToString();
			this->x_h_min->Text = "любой х";
		}

		// Добавлем фиктивную точку
		this->chart1->Series[0]->Points->AddXY(x[x.size() - 1], v[x.size() - 1]);
		this->chart1->Series[1]->Points->AddXY(x[x.size() - 1], u[x.size() - 1]);
		// Делаем ее невидимой
		int count = this->chart1->Series[0]->Points->Count;
		this->chart1->Series[0]->Points[count - 1]->IsEmpty = true;
		count = this->chart1->Series[1]->Points->Count;
		this->chart1->Series[1]->Points[count - 1]->IsEmpty = true;
	}

	void main1() {
		this->Table_for_test_task->Rows->Clear();
		std::vector<double> x,v; //численная траектория
		std::vector<double> characteristics_with_control_lp; //S*, Vудв, V'удв
		double NMAX;
		double max_olp = 0;//оценка локальной погрешности
		int n = 0; //номер шага
		double v0, x0=0, eps_gr; //начальные условия и eps(гр)
		int increase_h = 0, decrease_h = 0; //кол-во увеличений и уменьшений шага
		int c1, c2;
		double h, b, eps, h_prev; //шаг, правая граница, параметр контроля eps, предыдущий шаг
		double h_min, h_max, xh_max, xh_min;
		bool f = checkBox1->Checked; //выбран ли контроль лп 
		v0 = Convert::ToDouble(this->u0->Text);
		x.push_back(x0);
		v.push_back(v0);
		h = Convert::ToDouble(this->h0->Text);
		h_prev = h;
		h_min = h;
		h_max = h;
		eps_gr = Convert::ToDouble(this->eps_gr->Text);
		b = Convert::ToDouble(this->b->Text);
		NMAX = Convert::ToDouble(this->Nmax->Text);
		if ((f == 1) && (this->eps->Text != ""))
			eps = Convert::ToDouble(this->eps->Text);
		this->chart1->ChartAreas[0]->AxisX->Minimum = 0;
		this->chart1->ChartAreas[0]->AxisX->Maximum = b;
		this->Table_for_test_task->Rows->Add(0, x0, v0, " ", " ", " ", h, "", "", v0, 0);

		int i = 1;
		while (i <= NMAX) {
			c2 = 0; c1 = 0;
			if ((x[n] > b - eps_gr) || (x[n] >= b)) break;
			if (f == 1) {
				h_prev = h;
				characteristics_with_control_lp = method_RK_4_with_control_lp(f2, n, x, v, h, eps, c2, c1, max_olp, b);
				if (c1 == c2) {
					c1 = 0;
					c2 = 0;
				}
				increase_h += c2;
				decrease_h += c1;
				if ((h >= h_max) || (i == 1)) {
					h_max = h;
					xh_max = x[i];
				}
				if ((h <= h_min) || (i == 1)) {
					h_min = h;
					xh_min = x[i];
				}
			}
			else {
				method_RK_4(f2, n, x, v, h);
			}
			if (f == 1)
				this->Table_for_test_task->Rows->Add(i, x[i], v[i], characteristics_with_control_lp[1], v[i] - characteristics_with_control_lp[1], characteristics_with_control_lp[0], h, c1,c2, "-", "-");
			else
				this->Table_for_test_task->Rows->Add(i, x[i], v[i], "-", "-", "-", h, "-", "-", "-", "-");
			i++;
		}
		for (int i = 0; i < x.size(); i++) {
			if ((v[i]<1E+28)&&(v[i] >-1E+28))
				this->chart1->Series[0]->Points->AddXY(x[i], v[i]);
		}

		this->n->Text = (n).ToString();
		this->xN->Text = (x[x.size() - 1]).ToString();
		this->vN->Text = (v[v.size() - 1]).ToString();
		this->b_xN->Text = (b - x[x.size() - 1]).ToString();
		this->x_max_ui_vi->Text = "-";
		this->dec_h->Text = (decrease_h).ToString(); 
		this->inc_h->Text = (increase_h).ToString(); 
		this->max_olp->Text = (max_olp).ToString();
		if (f == 1) {
			this->max_h->Text = (h_max).ToString();
			this->x_h_max->Text = (xh_max).ToString();
			this->min_h->Text = (h_min).ToString();
			this->x_h_min->Text = (xh_min).ToString();
		}
		else {
			this->max_h->Text = (h_max).ToString();
			this->x_h_max->Text = "любой х";
			this->min_h->Text = (h_max).ToString();
			this->x_h_min->Text = "любой х";
		}

		// Добавлем фиктивную точку
		this->chart1->Series[0]->Points->AddXY(x[x.size() - 1], v[x.size() - 1]);
		// Делаем ее невидимой
		int count = this->chart1->Series[0]->Points->Count;
		this->chart1->Series[0]->Points[count - 1]->IsEmpty = true;
	}

	void main2() {
		this->Table_for_test_task->Rows->Clear();
		std::vector<double> x, v1,v2; //численная траектория
		std::vector<double> characteristics_with_control_lp; //S*, Vудв, V'удв
		double NMAX;
		double max_olp = 0;//оценка локальной погрешности
		int n = 0; //номер шага
		double v01,v02, x0 = 0, eps_gr; //начальные условия и eps(гр)
		int increase_h = 0, decrease_h = 0;//кол-во увеличений и уменьшений шага
		int c1, c2;
		double h, b, eps, h_prev; //шаг, правая граница, параметр контроля eps, предыдущий шаг
		double h_min, h_max, xh_max, xh_min;
		double a;
		bool f = checkBox1->Checked; //выбран ли контроль лп 
		a= Convert::ToDouble(this->a->Text);
		v01 = Convert::ToDouble(this->u0->Text);
		v02 = Convert::ToDouble(this->u0_pr->Text);
		x.push_back(x0);
		v1.push_back(v01);
		v2.push_back(v02);
		h = Convert::ToDouble(this->h0->Text);
		h_prev = h;
		h_min = h;
		h_max = h;
		eps_gr = Convert::ToDouble(this->eps_gr->Text);
		b = Convert::ToDouble(this->b->Text);
		NMAX = Convert::ToDouble(this->Nmax->Text);
		if ((f == 1) && (this->eps->Text != ""))
			eps = Convert::ToDouble(this->eps->Text);
		this->chart1->ChartAreas[0]->AxisX->Minimum = 0;
		this->chart1->ChartAreas[0]->AxisX->Maximum = b;
		this->Table_for_test_task->Rows->Add(0, x0, v01, " ", " ", " ", h, "", "", v01, 0);

		int i = 1;
		while (i <= NMAX) {
			c1 = 0;
			c2 = 0;
			if ((x[n] > b - eps_gr) || (x[n] >= b)) break;
			if (f == 1) {
				h_prev = h;
				characteristics_with_control_lp = method_RK_4_with_control_lp_for_system(f3, f4, a, n, x, v1,v2, h, eps, c2, c1, max_olp,b);
				if (c1 == c2) {
					c1 = 0;
					c2 = 0;
				}
				increase_h += c2;
				decrease_h += c1;
				if ((h >= h_max) || (i == 1)) {
					h_max = h;
					xh_max = x[i];
				}
				if ((h <= h_min) || (i == 1)) {
					h_min = h;
					xh_min = x[i];
				}
			}
			else {
				method_RK_4_for_system(f3,f4,a, n, x, v1,v2, h);
			}
			if (f == 1)
				this->Table_for_test_task->Rows->Add(i, x[i], v1[i], characteristics_with_control_lp[1], v1[i] - characteristics_with_control_lp[1], characteristics_with_control_lp[0], h, c1, c2, "-", "-");
			else
				this->Table_for_test_task->Rows->Add(i, x[i], v1[i], "-", "-", "-", h, "-", "-", "-", "-");
			i++;
		}
		for (int i = 0; i < x.size(); i++) {
			if (this->comboBox2->SelectedIndex == 0)
				if ((v1[i] < 1E+28) && (v1[i] > -1E+28))
					this->chart1->Series[0]->Points->AddXY(x[i], v1[i]);
			if (this->comboBox2->SelectedIndex == 1)
				if ((v2[i] < 1E+28) && (v2[i] > -1E+28))
					this->chart1->Series[0]->Points->AddXY(x[i], v2[i]);
			if (this->comboBox2->SelectedIndex == 2)
				if ((v2[i] < 1E+28) && (v2[i] > -1E+28)&& (v1[i] < 1E+28) && (v1[i] > -1E+28))
					this->chart1->Series[0]->Points->AddXY(v1[i], v2[i]);
		}

		this->n->Text = (n).ToString();
		this->xN->Text = (x[x.size() - 1]).ToString();
		this->vN->Text = (v1[v1.size() - 1]).ToString();
		this->b_xN->Text = (b - x[x.size() - 1]).ToString();
		this->x_max_ui_vi->Text = "-";
		this->dec_h->Text = (decrease_h).ToString(); 
		this->inc_h->Text = (increase_h).ToString();
		this->max_olp->Text = (max_olp).ToString();
		if (f == 1) {
			this->max_h->Text = (h_max).ToString();
			this->x_h_max->Text = (xh_max).ToString();
			this->min_h->Text = (h_min).ToString();
			this->x_h_min->Text = (xh_min).ToString();
		}
		else {
			this->max_h->Text = (h_max).ToString();
			this->x_h_max->Text = "любой х";
			this->min_h->Text = (h_max).ToString();
			this->x_h_min->Text = "любой х";
		}

		// Добавлем фиктивную точку
		this->chart1->Series[0]->Points->AddXY(x[x.size() - 1], v1[x.size() - 1]);
		// Делаем ее невидимой
		int count = this->chart1->Series[0]->Points->Count;
		this->chart1->Series[0]->Points[count - 1]->IsEmpty = true;
	}


	private:System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		switch (this->comboBox1->SelectedIndex) {
			case 0: test(); break;
			case 1: main1(); break;
			case 2: main2(); break;
		}
	}


	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->chart1->Series[0]->Points->Clear();
		this->chart1->Series[1]->Points->Clear();
		this->Table_for_test_task->Rows->Clear();
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->comboBox1->SelectedIndex == 2) {
			this->u0_pr->Visible = true;
			this->label1->Visible = true;
			this->label2->Visible = true;
			this->label22->Visible = true;
			pictureBox1->Image = Image::FromFile("D:\\Учеба\\ЧМ\\Lab\\task3.png");
			this->comboBox2->Visible = true;
			this->b->Text = "20";
			this->a->Visible = true;
		}
		if (this->comboBox1->SelectedIndex != 0){
			this->label20->Visible = false;
			this->max_ui_vi->Visible = false;
			this->label21->Visible = false;
			this->x_max_ui_vi->Visible = false;
			this->Column10->Visible = false;
			this->Column11->Visible = false;
			this->chart1->Series[1]->IsVisibleInLegend =false;
		}
		if (this->comboBox1->SelectedIndex == 0) {
			this->u0->Text = "1";
			this->b->Text = "5";
			pictureBox1->Image = Image::FromFile("D:\\Учеба\\ЧМ\\Lab\\task1.png");
			this->label20->Visible = true;
			this->label2->Visible = false;
			this->label22->Visible = false;
			this->max_ui_vi->Visible = true;
			this->label21->Visible = true;
			this->x_max_ui_vi->Visible = true;
			this->comboBox2->Visible = false;
			this->a->Visible = false;
			this->Column10->Visible = true;
			this->Column11->Visible = true;
			this->chart1->Series[1]->IsVisibleInLegend = true;
		}
		if (this->comboBox1->SelectedIndex == 1) {
			this->u0->Text="1";
			this->b->Text ="0,58";
			this->label22->Visible = false;
			pictureBox1->Image = Image::FromFile("D:\\Учеба\\ЧМ\\Lab\\task2.png");
			this->comboBox2->Visible = false;
			this->a->Visible = false;
			this->label2->Visible = false;
		}
	}
private: System::Void comboBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {





























}
};
}
