## 根据Shape文件生成的txt文件格式
### Slot_details_shp.txt (From slot.shp)
对于所有坐标都用(x|y|z)来描述，Slot的Geometry固定包含五个点，首尾相同
|slot id|link id|entryLine|Geometry(Polygon)|
|-------|-------|---------|-----------------|
|9000|9002|1|POLYGON((-4.96760919\|-4.88976726\|0,-6.14617265\|-10.01724132\|0,-8.5914249\|-9.6041403\|0,-7.204628\|-4.4503746\|0,-4.96760919\|-4.88976726\|0))|
### Junction_details_shp.txt (From junction.shp)
这里的坐标是单个点，用 X 和 Y 来分开描述， link ids用分号隔开
|junction id|link ids|Geometry X|Geometry Y|
|-----------|--------|----------|----------|
|9000|9002;9003|7.9767389|0.210041|
### Link_details_shp.txt (From link.shp)
|link id|fjcid|tjcid|width|Geometry(Polyline)|
|-------|-----|-----|-----|------------------|
|9000|9001|9002|166|LINESTRING(9.3102112\|21.3413677\|0,7.4145136\|22.8352985\|0,...)
