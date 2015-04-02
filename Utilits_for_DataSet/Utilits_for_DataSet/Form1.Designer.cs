namespace Utilits_for_DataSet
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menu = new System.Windows.Forms.MenuStrip();
            this.файлToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.открытьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.выходToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.окнаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.количествоToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem7 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem6 = new System.Windows.Forms.ToolStripMenuItem();
            this.изображенияToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.отметитьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.удавитьТекущийСписокToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.показатьСледующиеИзображенияToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.соъраитьСписокФайловToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.label = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.menu.SuspendLayout();
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.файлToolStripMenuItem,
            this.окнаToolStripMenuItem,
            this.изображенияToolStripMenuItem});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(986, 24);
            this.menu.TabIndex = 0;
            this.menu.Text = "menuStrip1";
            // 
            // файлToolStripMenuItem
            // 
            this.файлToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.открытьToolStripMenuItem,
            this.выходToolStripMenuItem});
            this.файлToolStripMenuItem.Name = "файлToolStripMenuItem";
            this.файлToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.файлToolStripMenuItem.Text = "Файл";
            // 
            // открытьToolStripMenuItem
            // 
            this.открытьToolStripMenuItem.Name = "открытьToolStripMenuItem";
            this.открытьToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.открытьToolStripMenuItem.Text = "Открыть";
            this.открытьToolStripMenuItem.Click += new System.EventHandler(this.открытьToolStripMenuItem_Click);
            // 
            // выходToolStripMenuItem
            // 
            this.выходToolStripMenuItem.Name = "выходToolStripMenuItem";
            this.выходToolStripMenuItem.Size = new System.Drawing.Size(121, 22);
            this.выходToolStripMenuItem.Text = "Выход";
            this.выходToolStripMenuItem.Click += new System.EventHandler(this.выходToolStripMenuItem_Click);
            // 
            // окнаToolStripMenuItem
            // 
            this.окнаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.количествоToolStripMenuItem});
            this.окнаToolStripMenuItem.Name = "окнаToolStripMenuItem";
            this.окнаToolStripMenuItem.Size = new System.Drawing.Size(47, 20);
            this.окнаToolStripMenuItem.Text = "Окна";
            // 
            // количествоToolStripMenuItem
            // 
            this.количествоToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.toolStripMenuItem3,
            this.toolStripMenuItem7,
            this.toolStripMenuItem4,
            this.toolStripMenuItem5,
            this.toolStripMenuItem6});
            this.количествоToolStripMenuItem.Name = "количествоToolStripMenuItem";
            this.количествоToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.количествоToolStripMenuItem.Text = "Количество";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem2.Text = "20";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem3.Text = "40";
            this.toolStripMenuItem3.Click += new System.EventHandler(this.toolStripMenuItem3_Click);
            // 
            // toolStripMenuItem7
            // 
            this.toolStripMenuItem7.Name = "toolStripMenuItem7";
            this.toolStripMenuItem7.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem7.Text = "50";
            this.toolStripMenuItem7.Click += new System.EventHandler(this.toolStripMenuItem7_Click);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem4.Text = "60";
            this.toolStripMenuItem4.Click += new System.EventHandler(this.toolStripMenuItem4_Click);
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem5.Text = "80";
            this.toolStripMenuItem5.Click += new System.EventHandler(this.toolStripMenuItem5_Click);
            // 
            // toolStripMenuItem6
            // 
            this.toolStripMenuItem6.Name = "toolStripMenuItem6";
            this.toolStripMenuItem6.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem6.Text = "100";
            this.toolStripMenuItem6.Click += new System.EventHandler(this.toolStripMenuItem6_Click);
            // 
            // изображенияToolStripMenuItem
            // 
            this.изображенияToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.отметитьToolStripMenuItem,
            this.удавитьТекущийСписокToolStripMenuItem,
            this.показатьСледующиеИзображенияToolStripMenuItem,
            this.соъраитьСписокФайловToolStripMenuItem});
            this.изображенияToolStripMenuItem.Name = "изображенияToolStripMenuItem";
            this.изображенияToolStripMenuItem.Size = new System.Drawing.Size(95, 20);
            this.изображенияToolStripMenuItem.Text = "Изображения";
            // 
            // отметитьToolStripMenuItem
            // 
            this.отметитьToolStripMenuItem.Name = "отметитьToolStripMenuItem";
            this.отметитьToolStripMenuItem.Size = new System.Drawing.Size(269, 22);
            this.отметитьToolStripMenuItem.Text = "Отметить последний";
            this.отметитьToolStripMenuItem.Click += new System.EventHandler(this.отметитьToolStripMenuItem_Click);
            // 
            // удавитьТекущийСписокToolStripMenuItem
            // 
            this.удавитьТекущийСписокToolStripMenuItem.Name = "удавитьТекущийСписокToolStripMenuItem";
            this.удавитьТекущийСписокToolStripMenuItem.Size = new System.Drawing.Size(269, 22);
            this.удавитьТекущийСписокToolStripMenuItem.Text = "Удалить текущий список";
            this.удавитьТекущийСписокToolStripMenuItem.Click += new System.EventHandler(this.удавитьТекущийСписокToolStripMenuItem_Click);
            // 
            // показатьСледующиеИзображенияToolStripMenuItem
            // 
            this.показатьСледующиеИзображенияToolStripMenuItem.Name = "показатьСледующиеИзображенияToolStripMenuItem";
            this.показатьСледующиеИзображенияToolStripMenuItem.Size = new System.Drawing.Size(269, 22);
            this.показатьСледующиеИзображенияToolStripMenuItem.Text = "Показать следующие изображения";
            this.показатьСледующиеИзображенияToolStripMenuItem.Click += new System.EventHandler(this.показатьСледующиеИзображенияToolStripMenuItem_Click);
            // 
            // соъраитьСписокФайловToolStripMenuItem
            // 
            this.соъраитьСписокФайловToolStripMenuItem.Name = "соъраитьСписокФайловToolStripMenuItem";
            this.соъраитьСписокФайловToolStripMenuItem.Size = new System.Drawing.Size(269, 22);
            this.соъраитьСписокФайловToolStripMenuItem.Text = "Сохранить список файлов";
            this.соъраитьСписокФайловToolStripMenuItem.Click += new System.EventHandler(this.соъраитьСписокФайловToolStripMenuItem_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Location = new System.Drawing.Point(67, 6);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(0, 13);
            this.label.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(974, 472);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 13);
            this.label1.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(986, 494);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label);
            this.Controls.Add(this.menu);
            this.MainMenuStrip = this.menu;
            this.Name = "Form1";
            this.Text = "Form1";
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.ToolStripMenuItem файлToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem открытьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem выходToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Label label;
        private System.Windows.Forms.ToolStripMenuItem окнаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem количествоToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem5;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem6;
        private System.Windows.Forms.ToolStripMenuItem изображенияToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem отметитьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem удавитьТекущийСписокToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem показатьСледующиеИзображенияToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem соъраитьСписокФайловToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem7;
        private System.Windows.Forms.Label label1;

    }
}

