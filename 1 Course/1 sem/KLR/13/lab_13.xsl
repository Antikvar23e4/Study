<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"> 
<xsl:template match="/">
<h2  align="center" style="color: #bbdaf0">Таблица зарплат</h2>
<table  align="center" border="1">
<xsl:for-each select="professions/head">
<tr style="color: #bbdaf0" align="center" bgcolor="#0000CD">
      <td><xsl:value-of select="hjob"/></td>
      <td><xsl:value-of select="hjunior"/></td>
      <td><xsl:value-of select="hmiddle"/></td>
      <td><xsl:value-of select="hsenior"/></td>
</tr>
</xsl:for-each>
<xsl:for-each select="professions/profession">
<xsl:sort select="job"/>
<tr style="color: #0000CD" align="center" bgcolor="#bbdaf0">
      <td><xsl:value-of select="job"/></td>
      <td><xsl:value-of select="junior"/></td>
      <td><xsl:value-of select="middle"/></td>
      <td><xsl:value-of select="senior"/></td>
</tr>
</xsl:for-each>
</table>
</xsl:template>
</xsl:stylesheet>