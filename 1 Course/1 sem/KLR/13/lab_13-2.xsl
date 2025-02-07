<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"> 
<xsl:template match="/">
<h2 style="color: #0000CD">Аттестация</h2>
<table border="1">
<xsl:for-each select="certification/head">
<tr style="color: #d9d9d9" align="center" bgcolor="#0000CD">
      <td ><xsl:value-of select="number"/></td>
      <td><xsl:value-of select="name"/></td>
      <td><xsl:value-of select="OAIP"/></td>
      <td><xsl:value-of select="inyaz"/></td>
      <td><xsl:value-of select="alov"/></td>
      <td><xsl:value-of select="fiz"/></td>
      <td><xsl:value-of select="TRPO"/></td>
      <td><xsl:value-of select="CYAR"/></td>
      <td><xsl:value-of select="LAiAG"/></td>
      <td><xsl:value-of select="MatA"/></td>
      <td><xsl:value-of select="SYAP"/></td>
</tr>
</xsl:for-each>
<xsl:for-each select="certification/person">
<tr style="color: #0000CD" align="center" bgcolor="#d9d9d9">
      <td style="color: #d9d9d9" bgcolor="#0000CD"><xsl:value-of select="hnumber"/></td>
      <td><xsl:value-of select="hname"/></td>

      <xsl:choose>
      <xsl:when test="hOAIP &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hOAIP"/></td>
      </xsl:when>
      <xsl:when test="hOAIP &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hOAIP"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hOAIP"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hinyaz &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hinyaz"/></td>
      </xsl:when>
      <xsl:when test="hinyaz &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hinyaz"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hinyaz"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="halov &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="halov"/></td>
      </xsl:when>
      <xsl:when test="halov &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="halov"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="halov"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hfiz &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hfiz"/></td>
      </xsl:when>
      <xsl:when test="hfiz &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hfiz"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hfiz"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hTRPO &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hTRPO"/></td>
      </xsl:when>
      <xsl:when test="hTRPO &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hTRPO"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hTRPO"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hCYAR &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hCYAR"/></td>
      </xsl:when>
      <xsl:when test="hCYAR &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hCYAR"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hCYAR"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hLAiAG &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hLAiAG"/></td>
      </xsl:when>
      <xsl:when test="hLAiAG &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hLAiAG"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hLAiAG"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hMatA &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hMatA"/></td>
      </xsl:when>
      <xsl:when test="hMatA &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hMatA"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hMatA"/></td>
      </xsl:otherwise>
      </xsl:choose>

      <xsl:choose>
      <xsl:when test="hSYAP &gt; 8">
      <td style="color: #d9d9d9" bgcolor="green"><xsl:value-of select="hSYAP"/></td>
      </xsl:when>
      <xsl:when test="hSYAP &lt; 4">
      <td style="color: #d9d9d9" bgcolor="red"><xsl:value-of select="hSYAP"/></td>
      </xsl:when>
      <xsl:otherwise>
      <td><xsl:value-of select="hSYAP"/></td>
      </xsl:otherwise>
      </xsl:choose>
</tr>
</xsl:for-each>
</table>
</xsl:template>
</xsl:stylesheet>