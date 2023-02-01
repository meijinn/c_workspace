# gnuplot 設定ファイル
# 最初に各種の設定をリセットする
reset

# 明示的に横軸と縦軸の範囲を決める
set xrange [ -6 : 6 ]
set yrange [ -250 : 250 ]

# 上と右の軸目盛りを表示しない
set xtics nomirror
set ytics nomirror

# 目盛りの刻み幅を指定
set xtics 1
set mxtics 2

set ytics 50
set mytics 5

set ticscale 2

# 軸名称を設定
set xlabel "Input voltage{/Times:Italic V}_{s} (V)"
set ylabel "Current {/Times:Italic I}_{1}, {/Times:Italic I}_{2}, {/Times:Italic I}_{3} (μA)"

# 凡例位置を指定
set key top left at -5, 235

#データから統計量を求める,先頭一行スキップ
stats "kadai1_2.txt" every ::1 u 1:4
sl1 = STATS_slope
ic1 = STATS_intercept
rs1 = STATS_correlation
#回帰直線の定義
ip1(x) = sl1 * x + ic1
# 決定係数，小数点第３位まで
r21 = sprintf("{/Times:Italic R}^{2}_{1} = %.3f", rs1 ** 2)

#データから統計量を求める,先頭一行スキップ
stats "data_sample.txt" every ::1 u 1:5
sl2 = STATS_slope
ic2 = STATS_intercept
rs2 = STATS_correlation
#回帰直線の定義
ip2(x) = sl2 * x + ic2
# 決定係数，小数点第３位まで
r22 = sprintf("{/Times:Italic R}^{2}_{2} = %.3f", rs2 ** 2)

#データから統計量を求める,先頭一行スキップ
stats "data_sample.txt" every ::1 u 1:6
sl3 = STATS_slope
ic3 = STATS_intercept
rs3 = STATS_correlation
#回帰直線の定義
ip3(x) = sl3 * x + ic3
# 決定係数，小数点第３位まで
r23 = sprintf("{/Times:Italic R}^{2}_{3} = %.3f", rs3 ** 2)

# 決定係数の表示，グラフ中の配置座標指定
set label r21 at 1, -50
set label r22 at 1, -100
set label r23 at 1, -150

# データと回帰直線をプロットする
plot "data_sample.txt" every ::1 u 1:4 title "{/Times:Italic I}_{1}" pt 1, ip1(x) notitle lt 4
replot "data_sample.txt" every ::1 u 1:5 title "{/Times:Italic I}_{2}" pt 5, ip2(x) notitle lt 5
replot "data_sample.txt" every ::1 u 1:6 title "{/Times:Italic I}_{3}" pt 9, ip3(x) notitle lt 6

# ファイル出力(emf形式)
set term emf monochrome font "Times New Roman,24" enhanced lw 2
set output "output_sample.emf"
replot
set output

# 端末の変更と後片付け
TERM = "Default"
set out
set term pop
reset