import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("HeapSortResults.csv", sep=";")
sns.set(style="whitegrid")

plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="seq_time", label="Sekvencijalno", marker="o")
sns.lineplot(data=df, x="n", y="par_time", hue="threads", marker="o", palette="tab10")
plt.title("Vrijeme izvršavanja (sekvencijalno vs paralelno) – Heap Sort")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Vrijeme (s)")
plt.legend(title="Broj tredova")
plt.tight_layout()
plt.show()

plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="speedup", hue="threads", marker="o", palette="tab10")
plt.title("Speedup paralelne verzije – Heap Sort")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Speedup")
plt.legend(title="Broj tredova")
plt.tight_layout()
plt.show()

plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="efficiency", hue="threads", marker="o", palette="tab10")
plt.title("Efikasnost paralelizacije – Heap Sort")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Efikasnost")
plt.legend(title="Broj tredova")
plt.tight_layout()
plt.show()
