
	EXTRN DATA	(isr_index)

	CSEG	AT	0103H		;32号 波形发生器5 中断入口
	MOV		isr_index, #32	;标记中断号32
	LJMP	006BH			;跳转到中断号13的向量
	
	CSEG	AT	010BH		;33号 波形发生器异常2 中断入口
	MOV		isr_index, #33	;标记中断号33
	LJMP	006BH			;跳转到中断号13的向量
	
	CSEG	AT	0113H		;34号 波形发生器异常4 中断入口
	MOV		isr_index, #34	;标记中断号34
	LJMP	006BH			;跳转到中断号13的向量
	
	CSEG	AT	011BH		;35号 触摸按键 中断入口
	MOV		isr_index, #35	;标记中断号35
	LJMP	006BH			;跳转到中断号13的向量
	
	CSEG	AT	0123H		;36号 RTC 中断入口
	MOV		isr_index, #36	;标记中断号36
	LJMP	006BH			;跳转到中断号13的向量
	

	END