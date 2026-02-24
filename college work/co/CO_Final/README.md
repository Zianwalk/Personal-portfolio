# 5-Stage Pipelined MIPS-Lite CPU Design

## 專案概述
本專案旨在使用 **Verilog HDL** 實作一個符合 MIPS 指令集架構的 **5-Stage Pipelined CPU**。  
從底層的運算邏輯單元（ALU）到複雜的流水線資料路徑（Datapath），完整模擬現代處理器處理指令的行為，並透過 **Modelsim** 進行功能驗證。

---

## 使用技術與工具
- **硬體描述語言**：Verilog HDL  
- **模擬開發環境**：Modelsim  
- **架構設計**：5-Stage Pipelined Datapath  
- **驗證與測試**：Testbench 檔案讀取、Waveform 波形分析  

---

## 技術核心與實作亮點

### 1. 支援 16 道 MIPS 核心指令集
系統完整實作以下類型指令，涵蓋運算、記憶體存取與分支跳躍：

- **整數運算**：`add, sub, and, or, sll, slt, addiu`  
- **記憶體存取**：`lw, sw` (Load Word / Store Word)  
- **分支與跳躍**：`beq, bne, j`  
- **進階運算**：實作 32-bit 無號數乘法指令 `multu` 及結果暫存器存取 `mfhi, mflo`  

---

### 2. 流水線架構 (5-Stage Pipelining)
嚴格遵循五階段流水線執行行為：

1. **IF (Instruction Fetch)**：指令擷取  
2. **ID (Instruction Decode)**：指令解碼與暫存器讀取  
3. **EX (Execution)**：整合 ALU 與 Multiplier 進行運算  
4. **MEM (Memory Access)**：資料記憶體存取  
5. **WB (Write Back)**：結果寫回暫存器  

---

### 3. 硬體模組化與驗證分析
- **模組化設計**：各功能單元（如 ALU, Multiplier）獨立模組化開發，便於擴展與維護  
- **自動化測試**：撰寫 Testbench，自動讀取 MIPS Machine Code 測試指令，驗證設計對不同資料集正確性  
- **時序圖分析**：透過 Modelsim 波形 (Waveform) 分析各階段訊號變化，排除 Data Hazard 或控制訊號錯誤  

---
