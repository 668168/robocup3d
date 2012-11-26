<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:output method="text"/>

  <xsl:template match="/">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="player-class/behaviors">
    digraph "test" {
    <xsl:for-each select="behavior">
      "<xsl:value-of select="@id"/>" [label="<xsl:value-of select="@type"/>:<xsl:value-of select="@id"/>"]
    </xsl:for-each>
    <xsl:for-each select="behavior">
      <!--      <xsl:param name="behaviorType" select="@type"/> -->
      <!--      <xsl:param name="behaviorId" select="@id"/> -->
      <xsl:for-each select="slot">
        "<xsl:value-of select="../@type"/>.<xsl:value-of select="@index"/>" [label="Slot <xsl:value-of select="@index"/>" shape="box"]
      "<xsl:value-of select="../@id"/>" -> "<xsl:value-of select="../@type"/>.<xsl:value-of select="@index"/>"
      <xsl:for-each select="behavior">
        "<xsl:value-of select="../../@type"/>.<xsl:value-of select="../@index"/>" -> "<xsl:value-of select="@refid"/>"[<xsl:if test="@commit = 1">color="blue"</xsl:if><xsl:if test="@scicc = 1"> headlabel="scicc"</xsl:if>]
      </xsl:for-each>
      </xsl:for-each>
    </xsl:for-each>
    }
  </xsl:template>

</xsl:stylesheet>
