<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="html" indent="yes"/>

<xsl:strip-space elements="*"/>
<xsl:variable name="file_ref_suffix">file_name</xsl:variable>

<xsl:template match="/">
	<html><xsl:text>
	</xsl:text><head><xsl:text>
		</xsl:text><title>Cheddar Project</title><xsl:text>
		</xsl:text>
		<meta http-equiv="content-style-type"
			content="text/css" /><xsl:text>
		</xsl:text>
		<link rel="stylesheet" type="text/css" href="cheddar_project.css" /><xsl:text>
	</xsl:text></head><xsl:text>
	</xsl:text><body><xsl:text>
		</xsl:text><table border="0" cellpadding="0" cellspacing="0">
			<!-- sommaire --><xsl:text>
			</xsl:text>
			<tr><xsl:text>
				</xsl:text><td><xsl:text>
					</xsl:text><a id="summary" />Summary : <br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr><xsl:text>
			</xsl:text>
			<xsl:apply-templates select="/cheddar/processors" mode="sommaire"/>
			<xsl:apply-templates select="/cheddar/tasks" mode="sommaire"/>
			<xsl:apply-templates select="/cheddar/resources" mode="sommaire"/>
			<xsl:apply-templates select="/cheddar/buffers" mode="sommaire"/>
			<xsl:apply-templates select="/cheddar/messages" mode="sommaire"/>
			<xsl:apply-templates select="/cheddar/dependencies" mode="sommaire"/>
			<!-- transition -->
			<tr><xsl:text>
				</xsl:text><td><xsl:text>
					</xsl:text><p> &#0160;</p><xsl:text>
					</xsl:text><p> &#0160;</p><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr>
			<!-- les tableaux --><xsl:text>
			</xsl:text>
			<xsl:apply-templates select="/cheddar/processors" mode="liste"/>
			<xsl:apply-templates select="/cheddar/tasks" mode="liste"/>
			<xsl:apply-templates select="/cheddar/resources" mode="liste"/>
			<xsl:apply-templates select="/cheddar/buffers" mode="liste"/>
			<xsl:apply-templates select="/cheddar/messages" mode="liste"/>
			<xsl:apply-templates select="/cheddar/dependencies" mode="liste"/>
			<!-- fin du tableau et du body --><xsl:text>
		</xsl:text></table><xsl:text>
	</xsl:text></body><xsl:text>
</xsl:text></html>
</xsl:template>

<!-- intitule' des liens dans le sommaire (et nom des éléments correspondants dans la suite du document) -->
<xsl:template name="soustitre">
	<xsl:if test="./name/text() != ''">
		<xsl:value-of select="concat(name(),' ',./name/text())"/>
	</xsl:if>
	<xsl:if test="(count(./name) = 0) or (./name/text() = '')">
		<xsl:value-of select="concat(name(),' #',position())"/>
	</xsl:if>
</xsl:template>

<!-- affichage de la partie du sommaire associée à un des fils de l'élément racine cheddar -->
<xsl:template match="/cheddar/*" mode="sommaire">
			<tr><xsl:text>
				</xsl:text><td  class="sommaire_titre"><xsl:text>
					</xsl:text><xsl:value-of select="count(./*)"/><xsl:text> </xsl:text>
					<xsl:choose>
						<xsl:when test="count(./*)=1">
							<xsl:value-of select="name(./*)"/> : <br />
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="name()"/> : <br />
						</xsl:otherwise>
					</xsl:choose><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr><xsl:text>
			</xsl:text>
			<xsl:for-each select="./*">
			<tr><xsl:text>
				</xsl:text><td class="sommaire_element"><xsl:text>
					</xsl:text><xsl:variable name="anchor" select="concat(name(),position())" />
					<xsl:text>&#0160;- </xsl:text>
					<xsl:element name="a">
						<xsl:attribute name="href">#<xsl:value-of select="$anchor"/></xsl:attribute>
						<xsl:call-template name="soustitre"/>
					</xsl:element><br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr><xsl:text>
			</xsl:text>
			</xsl:for-each>
</xsl:template>

<!-- affichage du détail d'un des fils de l'élément racine cheddar -->
<xsl:template match="/cheddar/*" mode="liste">
			<tr><xsl:text>
				</xsl:text><td class="titre"><xsl:text>
					</xsl:text><xsl:value-of select="name()"/> : <br />
					<br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr><xsl:text>
			</xsl:text>
			<!-- pour chaque élément... -->
			<xsl:for-each select="./*">
			<tr><xsl:text>
				</xsl:text><td class="element">
					<!-- ancre --><xsl:text>
					</xsl:text>
					<xsl:variable name="anchor" select="concat(name(),position())" />
					<xsl:element name="a">
						<xsl:attribute name="id"><xsl:value-of select="$anchor"/></xsl:attribute></xsl:element>
					<xsl:call-template name="soustitre"/><br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text>
			</tr>
			<!-- le tableau des données --><xsl:text>
			</xsl:text>
			<tr class="element_content"><xsl:text>
				</xsl:text>
				<td><xsl:text>
					</xsl:text><xsl:call-template name="element"/>
				</td><xsl:text>
			</xsl:text></tr>
			<!-- retour au sommaire --><xsl:text>
			</xsl:text>
			<tr class="element_content"><xsl:text>
				</xsl:text><td class="retour_sommaire"><xsl:text>
					</xsl:text><xsl:element name="a">
						<xsl:attribute name="href">#summary</xsl:attribute>back</xsl:element><br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr><xsl:text>
			</xsl:text>
			<tr class="element_content"><xsl:text>
				</xsl:text><td><xsl:text>
					</xsl:text>&#0160;<br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr>
			</xsl:for-each><xsl:text>
			</xsl:text>
			<!-- une ligne vide à la fin de chaque liste -->
			<tr><xsl:text>
				</xsl:text><td><xsl:text>
					</xsl:text>&#0160;<br /><xsl:text>
					</xsl:text>&#0160;<br /><xsl:text>
					</xsl:text>&#0160;<br /><xsl:text>
				</xsl:text></td><xsl:text>
			</xsl:text></tr><xsl:text>
			</xsl:text>
</xsl:template>

<!-- affichage de la valeur d'un attribut, ou du texte d'un élément, sachant qu'il peut s'agir d'un lien vers un fichier -->
<xsl:template name="maybe_link_value">
	<xsl:param name="name" select="name(.)"/>
	<xsl:param name="value"><xsl:value-of select="."/></xsl:param>
	<!-- interprêter la valeur de l'attribut comme une référence à un fichier ? -->
	<xsl:variable name="start_of_suffix"
		select="string-length($name) - string-length($file_ref_suffix) + 1"/>
	<xsl:variable name="is_file_ref" select="not($start_of_suffix &lt; 1) and 
			( substring($name, $start_of_suffix, string-length($file_ref_suffix))
			 = $file_ref_suffix )"/>
	<!-- si oui, alors lien externe vers le fichier -->
	<xsl:if test="$is_file_ref">
		<xsl:element name="a">
			<xsl:attribute name="href"><xsl:value-of select="$value"/></xsl:attribute>
			<xsl:attribute name="target">_blank</xsl:attribute>
			<xsl:value-of select="$value"/>
		</xsl:element>
	</xsl:if>
	<!-- sinon, alors simple affichage de la valeur -->
	<xsl:if test="not($is_file_ref)">
		<xsl:value-of select="$value"/>
	</xsl:if>
</xsl:template>

<!-- affichage d'un élément qui est, au moins, le petit-fils de l'élément racine -->
<xsl:template name="element">
					<table width="100%" cellpadding="1" cellspacing="1" class="boite">
						<!-- attributs -->
						<xsl:for-each select="@*">
						<xsl:text>
						</xsl:text>
						<tr class="attribut"><xsl:text>
							</xsl:text><td width="150" class="nom"><xsl:value-of select="name(.)"/></td><xsl:text>
							</xsl:text><td class="valeur">
								<xsl:call-template name="maybe_link_value"/>
							</td><xsl:text>
						</xsl:text></tr>
						</xsl:for-each>
						<!-- enfants -->
						<xsl:for-each select="./*"><xsl:text>
						</xsl:text>
						<tr class="enfant"><xsl:text>
							</xsl:text><td width="150" class="enfant" valign="top">
								<span class="nom"><xsl:value-of select="name()"/></span>
							</td><xsl:text>
							</xsl:text><td class="valeur">
								<xsl:call-template name="element"/>
							</td><xsl:text>
						</xsl:text></tr>
						</xsl:for-each>
						<!-- texte -->
						<tr class="text"><xsl:text>
							</xsl:text>
							<xsl:if test="normalize-space(text()) != ''">
								<td colspan="2" class="valeur">
									<xsl:call-template name="maybe_link_value">
										<xsl:with-param name="value" select="text()"/>
									</xsl:call-template>
								</td>
							</xsl:if>
							<xsl:text>
						</xsl:text></tr>
						<!-- fin du tableau -->
						<xsl:text>
					</xsl:text>
					</table><xsl:text>
				</xsl:text>
</xsl:template>
	
</xsl:stylesheet>
